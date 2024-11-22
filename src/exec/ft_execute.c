/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfortuna <mfortuna@student.42.pt>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 11:34:48 by mfortuna          #+#    #+#             */
/*   Updated: 2024/11/22 15:25:43 by mfortuna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int	ft_exec_pipe(t_data *data);

/*void list_open_fds(void)
{
    DIR *dir;
    struct dirent *entry;
    char path[256];

    snprintf(path, sizeof(path), "/proc/%d/fd", getpid());
    dir = opendir(path);
    if (dir == NULL)
    {
        perror("opendir");
        return;
    }

    printf("Open file descriptors:\n");
    while ((entry = readdir(dir)) != NULL)
    {
        if (entry->d_name[0] != '.')
        {
            printf("FD: %s\n", entry->d_name);
        }
    }
    closedir(dir);
}

void close_open_fds(void)
{
    DIR *dir;
    struct dirent *entry;
    char path[256];
    int fd;
    pid_t pid;

    // Obtém o PID do processo atual
    pid = getpid();

    // Constrói o caminho para o diretório de descritores de arquivo do processo atual
    snprintf(path, sizeof(path), "/proc/%d/fd", pid);

    dir = opendir(path);
    if (dir == NULL)
    {
        perror("opendir");
        return;
    }

	while ((entry = readdir(dir)) != NULL)
	{
		if (entry->d_name[0] != '.')
		{
			fd = ft_atoi(entry->d_name);
			if (fd > 2) // Não fechar stdin (0), stdout (1) e stderr (2)
			{
				close(fd);
				//printf("Closed FD: %d\n", fd);
			}
		}
	}
	closedir(dir);
}*/

void	ft_execve(t_data *data, t_cmd *cmd)
{
	pid_t	pid;

	//set_path(data);
	pid = fork();
	printf("Path: %s\n", cmd->path);
	printf("Cmd: %s\n", cmd->cmd[0]);
	if (pid < 0)
		return (perror("fork"));
	else if (pid == 0)
	{
		if (check_for_built(data, data->cmd) <= 1)
		{
			ms_bomb(data, 0);
			exit(0);
		}
		if (cmd->path == NULL)
		{
			ft_printf("%s: command not found\n", cmd->cmd[0]);
			exit (127);
		}
		else
		{
			if (strstr(cmd->path, ".sh") != NULL)
            {
                //char *args[] = {"/bin/bash", cmd->path, NULL};
                execve("/bin/bash", cmd->cmd, NULL);
            }
			else
				execve(cmd->path, cmd->cmd, NULL);
		}
		ms_bomb(data, 0);
		exit(0);
	}
	waitpid(pid, 0, 0);
}

void	init_redic(t_data *data)
{
	t_cmd	*cmd;

	cmd = data->cmd;
	data->pipe_n = NULL;
	while (cmd)
	{
		cmd->in_n = data->n_cmd;
		cmd->out_n = data->n_cmd;
		cmd = cmd->next;
	}
}

int	ft_exec_pipe(t_data *data)
{
	if (!data || !data->cmd)
		return (0);
    // Inicializa os pipes
	if (ft_init_pipe(data) == 0)
		return (0);
    // Executa os comandos
	exec_first_command(data);
	exec_intermediate_commands(data);
	exec_last_command(data);
    // Fecha todos os pipes no processo pai
	close_all_pipes(data);
	// Espera todos os processos filhos terminarem
	wait_for_children(data);
	return (1);
}

/*void	print_pipe_n(t_data *data)
{
	int	i;

	i = 0;
	printf("I: %d\n", i);
	if (!data->pipe_n)
	{
		printf("pipe_n is NULL\n");
		return;
	}
	while (i < data->n_cmd)
	{
		printf("Cmd[%d]: %s\n", i, data->cmd->cmd[0]);
		printf("N_cmd: %d\n", data->n_cmd);
		if (data->pipe_n[i] == NULL)
		{
			printf("Pipe[%d] is NULL\n", i);
			free_pipe_n(data);
			return;
		}
		else
		{
			printf("Pipe[%d][0]: %d\n", i, data->pipe_n[i][0]);
			printf("Pipe[%d][1]: %d\n", i, data->pipe_n[i][1]);
		}
		data->cmd = data->cmd->next;
		i++;
	}
	free_pipe_n(data);
}*/

void	free_pipe_n(t_data *data)
{
	int	i;

	i = 0;
	if (data->pipe_n)
	{
		while (i < data->n_cmd - 1)
		{
			if (data->pipe_n[i])
				free(data->pipe_n[i]);
			i++;
		}
		free(data->pipe_n);
	}
}

int	ft_execute(t_data *data)
{
	//int	cmd_idx;

	//ft_fork_sigset();
	init_redic(data);
	if (data->n_cmd == 1)
	{
		ft_execve(data, data->cmd);
		return (1);
	}
	if (ft_init_pipe(data) == 0)
		return (0);
	if (ft_exec_pipe(data) == 0 )
		return (0);
	//list_open_fds();
	//close_open_fds();
	close_all_pipes(data);
	//list_open_fds();
	free_pipe_n(data);
	data->n_cmd = 1;
	//ms_bomb(data, 1);
	/*if (ft_exec_first(data) == 0)
		return (0);
	cmd_idx = ft_exec_loop(data);
	if (cmd_idx == -1 )
		return (0);
	if (ft_exec_last(data) == 0)
		return (0);
	ft_close_pipe(data, NULL, NULL);
	wait(&g_exit);
	while (cmd_idx--)
		wait(&g_exit);
	wait(&g_exit);
	if (WIFSIGNALED(g_exit))
		g_exit = (128 + WTERMSIG(g_exit));
	else if (WIFEXITED(g_exit))
		g_exit = WEXITSTATUS(g_exit);*/
	return (1);
}

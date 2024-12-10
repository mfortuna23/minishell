/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfortuna <mfortuna@student.42.pt>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 11:34:48 by mfortuna          #+#    #+#             */
/*   Updated: 2024/11/20 10:53:33 by mfortuna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <stdio.h>
#include <stdlib.h>
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

    sprintf(path, "/proc/%d/fd", getpid());
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
            fd = atoi(entry->d_name);
            if (fd > 2) // Não fechar stdin (0), stdout (1) e stderr (2)
            {
                close(fd);
                //printf("Closed FD: %d\n", fd);
            }
        }
    }
    closedir(dir);
}

int		ft_test(t_data *data, t_cmd *cmd)
{
	(void)data;
	if (cmd->pipe)
		printf("Flag pipe\n"); //run_pipe(data, data->cmd); //
	else if (cmd->here_doc)
		printf("Flag Here_doc\n");
	else if (cmd->appen)
		printf("Flag Appen\n");
	else if (!cmd->pipe && !cmd->here_doc)
		printf("Flag cmd\n");
	ms_bomb(data, 0);
	close_open_fds();
	return (0);
}*/

void	ft_execve(t_data *data, t_cmd *cmd)
{
	pid_t	pid;

	//set_path(data);
	pid = fork();
	if (pid < 0)
		return (perror("fork"));
	else if (pid == 0)
	{
		ft_redir_in(cmd);
		ft_redir_out(cmd);
		if (check_for_built(data, data->cmd) <= 1)
		{
			ms_bomb(data, 0);
			exit(0);
		}
		if (cmd->path == NULL)//TODO Verificar se o comando existe
		{
			ft_printf("%s: command not found\n", cmd->cmd[0]);
			exit (127);
		}
		else
			execve(cmd->path, cmd->cmd, data->env);
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
void	ft_flags(t_data *data, t_cmd *cmd)
{
	if (cmd->here_doc)
	{
		printf("Flag Here_doc\n");
		//run_here_doc(data, data->cmd);
	}
	else
		ft_execve(data, cmd);
}


int	ft_execute(t_data *data, t_cmd *cmd)
{
	//int	cmd_idx;

	(void)cmd;
	//ft_fork_sigset();
	//print_cmds(data);
	init_redic(data);
	if (data->n_cmd == 1)
	{
		ft_flags(data, data->cmd);
		return (1);
	}
	if (ft_exec_pipe(data) == 0 )
		return (0);
	//print_pipe_n(data);
	data->n_cmd = 1;
	//ms_bomb(data, 1);
	return (1);
}

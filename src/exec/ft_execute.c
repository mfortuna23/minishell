/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfortuna <mfortuna@student.42.pt>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 11:34:48 by mfortuna          #+#    #+#             */
/*   Updated: 2024/11/18 11:00:24 by mfortuna         ###   ########.fr       */
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
}

void	run_pipe_child(t_data *data, t_cmd *cmd, int *fd, int i)
{
	(void)cmd;
	if (i == 0)
	{
		dup2(fd[1], STDOUT_FILENO);
		close(fd[0]);
		close(fd[1]);
		ft_test(data, cmd);
		//printf("Data: %d, Cmd: %s\n", data->n_tokens, cmd->cmd[0]); //ft_execve(data, cmd); //ft_execute(data);
		_exit(1);
	}
	else if (i == 1)
	{
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		close(fd[1]);
		ft_test(data, cmd);
		//printf("Data: %d, Cmd: %s\n", data->n_tokens, cmd->cmd[0]); //ft_execve(data, cmd); //ft_execute(data);
		_exit(1);
	}
	ms_bomb	(data, 0);
}

void	ft_pipes2(t_data *data, t_cmd *cmd, int i)
{
	int		fd[i];
	//int		status;
	t_cmd	*current;

	(void)cmd;
	(void)data;
	current = data->cmd;
	while (current)
	{
		printf("Cmd: %s\n", current->cmd[0]);
		fd[i] = '4';
		printf("Fd: %d\n", fd[i]);
		i--;
		current = current->next;
	}

}

void	run_pipe(t_data *data, t_cmd *cmd)// verificar quais são os cmd que estão entrando nessa função
{
	int		fd[2];
	int		status;
	int		pid1;
	int		pid2;
	t_cmd	*current;

	(void)cmd;
	current = data->cmd;
	printf("Cmd: %s\n", current->cmd[0]);
	//current->pipe = 0;
	//printf("Pipe 1: %d\n", current->pipe);
	if (pipe(fd) < 0)
		return (perror("pipe"));
	pid1 = fork();
	if (pid1 < 0)
		return (perror("fork"));
	printf("Pipe 1: %d\n", current->pipe);
	if (pid1 == 0)
	{
		run_pipe_child(data, current, fd, 0);
	}
	current = current->next;
	pid2 = fork();
	printf("Pipe 2: %d\n", current->pipe);
	if (pid2 < 0)
		return (perror("fork"));
	if (pid2 == 0 && current->pipe == 0)
		run_pipe_child(data, current, fd, 1);
	else if (pid2 == 0 && current->pipe == 1)
	{
		run_pipe_child(data, current, fd, 0);
	}
	close(fd[0]);
	close(fd[1]);
	waitpid(pid1, &status, 0);
	waitpid(pid2, &status, 0);
}
	//(void)data;
	if (cmd->pipe)
		ft_pipes2(data, data->cmd, 10); //printf("Flag pipe\n");
	else if (cmd->here_doc)
		printf("Flag Here_doc\n"); //ft_heredoc(current);
	else if (cmd->appen)
		printf("Flag append\n"); //ft_append(current);
	else if (!cmd->pipe && !cmd->here_doc)
		ft_execve(data, data->cmd); //printf("Flag cmd\n");

	return (0);

*/

void	ft_execve(t_data *data, t_cmd *cmd)
{
	pid_t	pid;

	//set_path(data);
	pid = fork();
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
			execve(cmd->path, cmd->cmd, NULL);
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

/*int	ft_exec_pipe(t_data *data)
{
    if (!data || !data->cmd)
        return 0;

    // Inicializa os pipes
    if (ft_init_pipe(data) == 0)
        return 0;

	t_cmd *current = data->cmd;
	int i = 0;

	// Primeiro comando
	current->pid = fork();
	if (current->pid < 0)
	{
		perror("fork");
		return (0);
	}
	if (current->pid == 0)
	{
		// Redireciona a saída padrão para o pipe
		if (dup2(data->pipe_n[0][1], STDOUT_FILENO) == -1)
		{
			perror("dup2");
			exit(EXIT_FAILURE);
		}
		printf("Pid first: %d\n", current->pid);
		close(data->pipe_n[0][0]);
		close(data->pipe_n[0][1]);
		ft_execve(data, current);
		exit(EXIT_FAILURE); // Se ft_execve falhar
	}

	// Comandos intermediários
	current = current->next;
	i = 1;
	while (i < data->n_cmd - 1)
	{
		current->pid = fork();
		if (current->pid < 0)
		{
			perror("fork");
			return (0);
		}
		if (current->pid == 0)
		{
			printf("Cmd[%d]: %s\n", i, current->cmd[0]);
			// Redireciona a entrada padrão para o pipe anterior
			if (dup2(data->pipe_n[i - 1][0], STDIN_FILENO) == -1)
			{
				perror("dup2");
				exit(EXIT_FAILURE);
			}
			// Redireciona a saída padrão para o próximo pipe
			if (dup2(data->pipe_n[i][1], STDOUT_FILENO) == -1)
			{
				perror("dup2");
				exit(EXIT_FAILURE);
			}
			printf("Pid middle: %d\n", current->pid);
			close(data->pipe_n[i - 1][0]);
			close(data->pipe_n[i - 1][1]);
			close(data->pipe_n[i][0]);
			close(data->pipe_n[i][1]);
			ft_execve(data, current);
			exit(EXIT_FAILURE); // Se ft_execve falhar
		}
		current = current->next;
		i++;
	}

	// Último comando
	current->pid = fork();
	if (current->pid < 0)
	{
		perror("fork");
		return (0);
	}
	if (current->pid == 0)
	{
		
		// Redireciona a entrada padrão para o pipe anterior
		if (dup2(data->pipe_n[data->n_cmd - 2][0], STDIN_FILENO) == -1)
		{
			perror("dup2");
			exit(EXIT_FAILURE);
		}
		printf("Pid Last: %d\n", current->pid);
		close(data->pipe_n[data->n_cmd - 2][0]);
		close(data->pipe_n[data->n_cmd - 2][1]);
		printf("Cmd[%d]: %s\n", i, current->cmd[0]);
		ft_execve(data, current);
		exit(EXIT_FAILURE); // Se ft_execve falhar
	}
	// Fecha todos os pipes no processo pai
	i = 0;
	while (i < data->n_cmd - 1)
	{
		close(data->pipe_n[i][0]);
		close(data->pipe_n[i][1]);
		i++;
	}

	// Espera todos os processos filhos terminarem
	i = 0;
	while (i < data->n_cmd)
	{
		wait(NULL);
		i++;
	}

	return (1);
}*/

int	ft_execute(t_data *data, t_cmd *cmd)
{
	//int	cmd_idx;

	(void)cmd;
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
	//print_pipe_n(data);
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfortuna <mfortuna@student.42.pt>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 11:34:48 by mfortuna          #+#    #+#             */
/*   Updated: 2024/11/14 11:58:25 by mfortuna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void list_open_fds(void)
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

void	ft_execve(t_data *data, t_cmd *cmd)
{
	pid_t	pid;

	//set_path(data);
	pid = fork();
	if (pid < 0)
		return (perror("fork"));
	else if (pid == 0)
	{
		if (check_for_built(data, data->cmd) == 0)
		{
			ms_bomb(data, 0);
			exit(0);
		}
		if (cmd->path == NULL)
			ft_printf("%s: command not found\n", cmd->cmd[0]);
		else 
			execve(cmd->path, cmd->cmd, NULL);
		ms_bomb(data, 0);
		close_open_fds();
		exit(0);
	}
	waitpid(pid, 0, 0);
	close_open_fds();
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

int		ft_execute(t_data *data, t_cmd *cmd)
{
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
}

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

void	clear_exit(t_data *data, int status)
{
	delete_cmds(data);
	del_lastenv(data);
	free(data->env);
	free(data->input);
	free(data->parser);
	exit(status);
}

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

void	set_path(t_data *data)
{
	t_cmd	*current;

	current = data->cmd;
	if (!current)
		exit(0);
	current->path_to_cmd = get_paths(data);
	while (current)
	{
		
		current->path = find_path(data, current->cmd[0]);
		current = current->next;
	}
}

void	run_pipe_child(t_data *data, t_cmd *cmd, int *fd, int i)
{
	if (i == 0)
	{
		dup2(fd[1], STDOUT_FILENO);
		close(fd[0]);
		close(fd[1]);
		ft_execve(data, cmd);
		ms_bomb(data, 0);
		_exit(1);
	}
	else if (i == 1)
	{
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		close(fd[1]);
		ft_execve(data, cmd);
		ms_bomb	(data, 0);
		_exit(1);
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
	if (pipe(fd) < 0)
		return (perror("pipe"));
	pid1 = fork();
	if (pid1 < 0)
		return (perror("fork"));
	if (pid1 == 0)
		run_pipe_child(data, current, fd, 0);
	current = current->next;
	pid2 = fork();
	if (pid2 < 0)
		return (perror("fork"));
	if (pid2 == 0)
		run_pipe_child(data, current, fd, 1);
	close(fd[0]);
	close(fd[1]);
	waitpid(pid1, &status, 0);
	waitpid(pid2, &status, 0);
}

int		ft_execute(t_data *data)
{
	//(void)data;
	if (data->cmd->pipe)
		run_pipe(data, data->cmd); //printf("Flag pipe\n");
	else if (data->cmd->here_doc)
		printf("Flag Here_doc\n"); //ft_heredoc(current);
	else if (data->cmd->appen)
		printf("Flag append\n"); //ft_append(current);
	else if (!data->cmd->pipe && !data->cmd->here_doc)
		ft_execve(data, data->cmd); //printf("Flag cmd\n");

	return (0);
}

/*void	ft_pipe(t_data *data)
{
	int		fd[2];
	pid_t	pid;

	pipe(fd);
	pid = fork();
	if (pid < 0)
		return (perror("fork"));
	if (pid == 0)
	{
		dup2(fd[1], 1);
		close(fd[0]);
		close(fd[1]);
		execve(data->cmd->path, data->cmd->full_tokens, data->env);
		exit(0);
	}
	else
	{
		dup2(fd[0], 0);
		close(fd[0]);
		close(fd[1]);
		ft_execute(data);
	}
}

void	ft_heredoc(t_data *data)
{
	int		fd[2];
	pid_t	pid;

	pipe(fd);
	pid = fork();
	if (pid < 0)
		return (perror("fork"));
	if (pid == 0)
	{
		dup2(fd[1], 1);
		close(fd[0]);
		close(fd[1]);
		execve(data->cmd->path, data->cmd->full_tokens, data->env);
		exit(0);
	}
	else
	{
		dup2(fd[0], 0);
		close(fd[0]);
		close(fd[1]);
		ft_execute(data);
	}
}*/

/* executes program */
// void	ft_execute(t_data *data)
// {
// 	pid_t	pid;

// 	pid = fork();
// 	if (pid < 0)
// 		return (perror("fork"));
// 	if (pid == 0)
// 	{
// 		execve(data->path, data->tokens, data->env);
// 		exit(0);
// 	}
// 	waitpid(pid, 0, 0);
// 	free(data->path);
// 	ft_freearr(data->tokens);
// }
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfortuna <mfortuna@student.42.pt>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 11:34:48 by mfortuna          #+#    #+#             */
/*   Updated: 2024/10/28 12:06:45 by mfortuna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/* executes program */
// void	ft_execute(t_data *data)
// {
// 	pid_t	pid;

// 	pid = fork();
// 	if (pid < 0)
// 		return (perror("fork"));
// 	if (pid == 0)
// 	{
// 		execve(data->path, data->tokens, data->env);
// 		exit(0);
// 	}
// 	waitpid(pid, 0, 0);
// 	free(data->path);
// 	ft_freearr(data->tokens);
// }
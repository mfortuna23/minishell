/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbezerra <tbezerra@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 11:34:48 by mfortuna          #+#    #+#             */
/*   Updated: 2024/11/12 10:50:12 by tbezerra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	clear_exit(t_data *data, int status)
{
	delete_cmds(data);
	del_lastenv(data);
	free(data->env);
	free(data->input);
	free(data->parser);
	exit(status);
}

void print_env(t_env *env)
{
    t_env *current = env;

    while (current)
    {
        printf("Full: %s,\nName: %s,\nValue: %s\n", current->full, current->name, current->value);
        current = current->next;
    }
}

void	ft_execve(t_data *data, t_cmd *cmd)
{
	pid_t	pid;

	pid = fork();
	//printf("PID 1: %d\n", pid);
	if (pid < 0)
		return (perror("fork"));
	if (check_for_built(data, data->cmd) == 0)
		exit(0);
	else if (pid == 0)
	{
		execve(cmd->path, cmd->cmd, NULL);
		exit(0);
	}
	waitpid(pid, 0, 0);
}

void	set_path(t_data *data)
{
	t_cmd	*current;

	current = data->cmd;
	if (!current)
		exit(0);
	while (current)
	{
		current->path_to_cmd = get_paths(data);
		current->path = find_path(data, current->cmd[0]);
		printf("Path: %s\n", current->path);
		current = current->next;
	}
}

void	run_pipe_child(t_data *data, t_cmd *cmd, int *fd, int i)
{
	if (i == 0)
	{
		dup2(fd[1], 1);
		close(fd[0]);
		close(fd[1]);
		printf("Pipe child 1\n");
		printf("Data 1: %s\n", data->cmd->cmd[0]);
		printf("Cmd 1:%s\n", cmd->cmd[0]);
		ft_execve(data, cmd);
		exit(0);
	}
	else if (i == 1)
	{
		dup2(fd[0], 0);
		close(fd[0]);
		close(fd[1]);
		printf("Pipe child 2\n");
		printf("Data 2: %s\n", data->cmd->cmd[0]);
		printf("Cmd 2:%s\n", cmd->cmd[1]);
		ft_execve(data, cmd);
		exit(0);
	}
}

void	run_pipe(t_data *data, t_cmd *cmd)// verificar quais são os cmd que estão entrando nessa função
{
	int		fd[2];
	int		status;
	int		pid1;
	int		pid2;
	t_cmd	*current;

	current = data->cmd;
	printf("data->cmd->cmd[0]: %s\n", data->cmd->cmd[0]);
	printf("Cmd:%s\n", cmd->cmd[0]);
	if (pipe(fd) < 0)
		return (perror("pipe"));
	pid1 = fork();
	if (pid1 == 0)
	{
		printf("Pipe 1\n");
		run_pipe_child(data, current, fd, 0);
	}
	current = current->next;
	pid2 = fork();
	if (pid2 == 0)
	{
		run_pipe_child(data, current, fd, 1);
	}
	close(fd[0]);
	close(fd[1]);
	waitpid(pid1, &status, 0);
	waitpid(pid2, &status, 0);
	//ms_bomb(data);
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
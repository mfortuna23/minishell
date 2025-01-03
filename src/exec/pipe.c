/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfortuna <mfortuna@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 11:14:25 by tbezerra          #+#    #+#             */
/*   Updated: 2025/01/03 00:12:03 by mfortuna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	wait_for_children(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->n_cmd)
	{
		wait(NULL);
		i++;
	}
}

void	close_all_pipes(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->n_cmd - 1)
	{
		close(data->pipe_n[i][0]);
		close(data->pipe_n[i][1]);
		free(data->pipe_n[i]);
		i++;
	}
	free(data->pipe_n);
	data->pipe_n = NULL;
}

void	exec_last_command(t_data *data)
{
	t_cmd	*current;

	current = data->cmd;
	while (current->next)
		current = current->next;
	current->pid = fork();
	if (current->pid < 0)
		error_exit("fork");
	if (current->pid == 0)
	{
		//ft_fprintf(2, 0, "a PID last cmd is %i\n", getpid()); // TODO remove
		if (dup2(data->pipe_n[data->n_cmd - 2][0], STDIN_FILENO) == -1)
			error_exit("dup2");
		close_all_pipes(data);
		ft_execve(data, current);
		exit(EXIT_FAILURE);
	}
}

void	exec_intermediate_commands(t_data *d)
{
	t_cmd	*current;
	int		i;

	current = d->cmd->next;
	i = 1;
	while (i < d->n_cmd - 1)
	{
		current->pid = fork();
		if (current->pid < 0)
			error_exit("fork");
		if (current->pid == 0)
		{
			//ft_fprintf(2, 0, "a PID of mid cmd is %i\n", getpid()); // TODO remove
			dup_pipes(d->pipe_n[i - 1][0], d->pipe_n[i][1], i, d->n_cmd);
			close_all_pipes(d);
			free(d->pipe_n);
			d->pipe_n = NULL;
			ft_execve(d, current);
			exit(EXIT_FAILURE);
		}
		else
			close_fds(d->pipe_n[i - 1][0], d->pipe_n[i - 1][1]);
		current = current->next;
		i++;
	}
}

void	exec_first_command(t_data *data)
{
	t_cmd	*current;

	current = data->cmd;
	//ft_fprintf(2, 2, "Dup2: FD_IN=%d FD_OUT=%d for command %s\n", current->fd_in, data->pipe_n[0], current->cmd[0]);
	current->pid = fork();
	if (current->pid < 0)
		error_exit("fork");
	if (current->pid == 0)
	{
		//ft_fprintf(2, 0, "a PID in first cmd is %i\n", getpid()); // TODO remove
		if (dup2(data->pipe_n[0][1], STDOUT_FILENO) == -1)
			error_exit("dup2");
		close_all_pipes(data);
		ft_execve(data, current);
		exit(EXIT_FAILURE);
	}
}

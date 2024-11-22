/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbezerra <tbezerra@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 11:14:25 by tbezerra          #+#    #+#             */
/*   Updated: 2024/11/21 23:17:47 by tbezerra         ###   ########.fr       */
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
		i++;
	}
}

void	exec_last_command(t_data *data)
{
	t_cmd	*current;

	current = data->cmd;
	while (current->next)
		current = current->next;
	current->pid = fork();
	if (current->pid < 0)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	if (current->pid == 0)
	{
		// Redireciona a entrada padrão para o pipe anterior
		if (dup2(data->pipe_n[data->n_cmd - 2][0], STDIN_FILENO) == -1)
		{
			perror("dup2");
			exit(EXIT_FAILURE);
		}
		close(data->pipe_n[data->n_cmd - 2][0]);
		close(data->pipe_n[data->n_cmd - 2][1]);
		ft_execve(data, current);
		exit(EXIT_FAILURE); // Se ft_execve falhar
	}
}

void	exec_intermediate_commands(t_data *data)
{
	t_cmd *current = data->cmd->next;
	int i = 1;

	while (i < data->n_cmd - 1)
	{
		current->pid = fork();
		if (current->pid < 0)
		{
			perror("fork");
			exit(EXIT_FAILURE);
		}
		if (current->pid == 0)
		{
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
			close(data->pipe_n[i - 1][0]);
			close(data->pipe_n[i - 1][1]);
			close(data->pipe_n[i][0]);
			close(data->pipe_n[i][1]);
			ft_execve(data, current);
			exit(EXIT_FAILURE); // Se ft_execve falhar
		}
		else
		{
			close(data->pipe_n[i - 1][0]);
			close(data->pipe_n[i - 1][1]);
		}
		current = current->next;
		i++;
	}
}

void	exec_first_command(t_data *data)
{
	t_cmd	*current;

	current = data->cmd;
	current->pid = fork();
	if (current->pid < 0)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	if (current->pid == 0)
	{
		// Redireciona a saída padrão para o pipe
		if (dup2(data->pipe_n[0][1], STDOUT_FILENO) == -1)
		{
			perror("dup2");
			exit(EXIT_FAILURE);
		}
		close(data->pipe_n[0][0]);
		close(data->pipe_n[0][1]);
		ft_execve(data, current);
		exit(EXIT_FAILURE); // Se ft_execve falhar
	}
}

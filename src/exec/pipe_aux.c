/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_aux.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbezerra <tbezerra@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 11:14:25 by tbezerra          #+#    #+#             */
/*   Updated: 2024/11/21 22:05:29 by tbezerra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*void	ft_exec_child_i(t_data *data, int i)
{
	t_cmd	*cmd;

	cmd = data->cmd->next;
	ft_exec_redir_set(data, cmd);
	ft_setter_pipe(data, i - 1, STDIN_FILENO);
	ft_setter_pipe(data, i, STDOUT_FILENO);
	ft_exec_child_inner(data, cmd);
}*/

int	ft_init_pipe(t_data *data)
{
	int	i;
	int	n_pipes;

	n_pipes = data->n_cmd - 1;
	i = 0;
	data->pipe_n = ft_calloc(n_pipes, sizeof(int *));
	while (i < n_pipes)
	{
		data->pipe_n[i] = ft_calloc(2, sizeof(int));
		if (pipe(data->pipe_n[i]) == -1)
			return (0);
		i++;
	}
	return (1);
}

/*int ft_init_pipe(t_data *data)
{
	int	i;
	int	n_pipes = 0;

	n_pipes = data->n_cmd - 1;
	i = 0;
	data->pipe_n = ft_calloc(n_pipes, sizeof(int *));
	if (!data->pipe_n)
		return (0);
	while (i < n_pipes)
	{
		data->pipe_n[i] = ft_calloc(2, sizeof(int));
		if (!data->pipe_n[i])
		{
		// Liberar memória alocada anteriormente em caso de erro
			while (i > 0)
				free(data->pipe_n[--i]);
			free(data->pipe_n);
			return (0);
		}
		if (pipe(data->pipe_n[i]) == -1)
		{
			perror("pipe");
			// Liberar memória alocada anteriormente em caso de erro
			while (i >= 0)
				free(data->pipe_n[i--]);
			free(data->pipe_n);
			return (0);
		}
		i++;
	}
	return (1);
}*/

/*int	ft_setter_pipe(t_data *data, int i, int out)
{
	if (out < 0 || out > 1)
		return (1);
	if (dup2(data->pipe_n[i][out], out) == -1)
	{
		ft_close_pipe(data, NULL, NULL);
		ft_fork_exit(data);
	}
	return (0);
}

int	ft_setter_pipe_fd(t_data *data, int fd, int std)
{
	if ((std > 1 || std < 0) && std != 10)
		return (1);
	if (dup2(fd, std) == -1)
	{
		ft_close_pipe(data, &fd, NULL);
		close(fd);
		ft_fork_exit(data);
	}
	return (0);
}*/

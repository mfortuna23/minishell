/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_aux.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfortuna <mfortuna@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 11:14:25 by tbezerra          #+#    #+#             */
/*   Updated: 2025/01/15 00:03:06 by mfortuna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_init_pipe(t_data *data)
{
	int	i;
	int	n_pipes;

	n_pipes = data->n_cmd - 1;
	i = 0;
	data->pipe_n = calloc(n_pipes, sizeof(int *));
	while (i < n_pipes)
	{
		data->pipe_n[i] = calloc(2, sizeof(int));
		if (pipe(data->pipe_n[i]) == -1)
			return (0);
		i++;
	}
	return (1);
}

void	close_fds(int fd_in, int fd_out)
{
	if (fd_in > 2)
		close(fd_in);
	if (fd_out > 2)
		close(fd_out);
}

void	dup_pipes(int fd_in, int fd_out, int current, int n_cmds)
{
	if (dup2(fd_in, STDIN_FILENO) == -1)
		error_exit("dup2");
	if (current < n_cmds && dup2(fd_out, STDOUT_FILENO) == -1)
		error_exit("dup2");
}

void	error_exit(char *error)
{
	perror(error);
	exit(EXIT_FAILURE);
}

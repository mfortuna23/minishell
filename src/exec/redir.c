/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbezerra <tbezerra@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 12:17:55 by tbezerra          #+#    #+#             */
/*   Updated: 2024/11/21 22:04:29 by tbezerra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_redir_out(t_cmd *cmd)
{
	int	fd_out;

	if (cmd->outfile)
	{
		if (cmd->appen)
			fd_out = open(cmd->outfile, O_CREAT | O_WRONLY | O_APPEND, 0644);
		else
			fd_out = open(cmd->outfile, O_CREAT | O_WRONLY | O_TRUNC, 0644);
		if (fd_out < 0)
		{
			perror("open");
			exit(EXIT_FAILURE);
		}
		if (dup2(fd_out, STDOUT_FILENO) < 0)
		{
			perror("dup2");
			close(fd_out);
			exit(EXIT_FAILURE);
		}
		close(fd_out);
	}
}
void	ft_redir_in(t_cmd *cmd)
{
	int	fd_in;

	if (cmd->infile)
	{
		fd_in = open(cmd->infile, O_RDONLY);
		if (fd_in < 0)
		{
			perror("open");
			exit(EXIT_FAILURE);
		}
		if (dup2(fd_in, STDIN_FILENO) < 0)
		{
			perror("dup2");
			close(fd_in);
			exit(EXIT_FAILURE);
		}
		close(fd_in);
	}
}

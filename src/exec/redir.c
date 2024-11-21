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

void	ft_redir_in(t_data *data, t_cmd *cmd)
{
	int	i;

	i = 0;
	while (i < cmd->in_n)
	{
		if (cmd->fd_in != -1 && i > 0)
		{
			close(cmd->fd_in);
			if (cmd->here_doc == true)
				unlink(cmd->infile);
			cmd->fd_in = -1;
		}
		cmd->fd_in = ft_type_redir(cmd + i);
		i++;
	}
	if (cmd->fd_in < 0)
		ft_fork_exit(data);
	/*if (ft_setter_pipe_fd(data, cmd->fd_in, STDIN_FILENO) == -1)
	{
		close(cmd->fd_in);
		ft_fork_exit(data);
	}*/
}

int	ft_type_redir(t_cmd *redir)
{
	int	ret;

	if (!redir->infile)
		return (-1);
	ret = open(redir->infile, O_RDONLY,
			S_IRWXU | S_IRGRP | S_IROTH);
	if (ret == -1)
		ft_no_file_err(redir->infile);
	return (ret);
}

void	ft_out_redir(t_data *data, t_cmd *cmd)
{
	int	i;

	i = 0;
	while (i < cmd->out_n)
	{
		if (cmd->fd_out != -1)
		{
			close(cmd->fd_out);
			cmd->fd_out = -1;
		}
		cmd->fd_in = open(cmd->outfile, O_CREAT | O_WRONLY
				| (O_APPEND * (cmd->appen == true)
					| (O_TRUNC * (cmd->appen == false))),
				S_IRWXU | S_IRGRP | S_IROTH);
		++i;
	}
	if (cmd->fd_out < 0)
		ft_fork_exit(data);
	/*if ((cmd->fd_in != 1)
		&& (ft_setter_pipe_fd(data, cmd->fd_out, STDOUT_FILENO) == -1))
	{
		close(cmd->fd_out);
		ft_fork_exit(data);
	}*/
}

void	ft_close_redir(int *in_fd, int *out_fd)
{
	if (in_fd && *in_fd != -1)
	{
		close(*in_fd);
		*in_fd = -1;
	}
	if (out_fd && *out_fd != -1)
	{
		close(*out_fd);
		*out_fd = -1;
	}
}
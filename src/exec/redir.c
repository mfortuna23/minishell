/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfortuna <mfortuna@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 12:17:55 by tbezerra          #+#    #+#             */
/*   Updated: 2025/01/03 12:28:40 by mfortuna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	open_out(t_data *data, char *name, bool ap)
{
	int	fd;

	if (ap)
		fd = open(name, O_CREAT | O_WRONLY | O_APPEND, 0644);
	else
		fd = open(name, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd < 0)
	{
		perror("open");
		ms_bomb(data, 0);
		exit(EXIT_FAILURE);
	}
	if (dup2(fd, STDOUT_FILENO) < 0)
	{
		perror("dup2");
		close(fd);
		ms_bomb(data, 0);
		exit(EXIT_FAILURE);
	}
	return (fd);
}

int	ft_redir_out(t_data *data, t_cmd *cmd)
{
	int			fd_out;
	t_outfile	*file;

	file = cmd->out_file;
	fd_out = 0;
	if (!file)
		return (fd_out);
	while (file->next != NULL)
	{
		fd_out = open_out(data, file->name, file->appen);
		close(fd_out);
		file = file->next;
	}
	fd_out = open_out(data, file->name, file->appen);
	return (fd_out);
}

int	try_open_in(t_data *data, char *name)
{
	int	fd;

	fd = open(name, O_RDONLY);
	if (fd < 0)
	{
		perror("open");
		ms_bomb(data, 0);
		exit(EXIT_FAILURE);
	}
	if (dup2(fd, STDIN_FILENO) < 0)
	{
		perror("dup2");
		close(fd);
		ms_bomb(data, 0);
		exit(EXIT_FAILURE);
	}
	return (fd);
}

int	ft_redir_in(t_data *data, t_cmd *cmd)
{
	t_infile	*file;
	int			fd;

	file = cmd->in_file;
	fd = 0;
	if (file == NULL)
		return (fd);
	while (file->next)
	{
		if (!file->here_doc)
		{
			fd = try_open_in(data, file->name);
			close (fd);
		}
		file = file->next;
	}
	if (file->here_doc)
	{
		cmd->here_doc = file;
		return (create_file(file, 0));
	}
	try_open_in(data, file->name);
	return (fd);
}

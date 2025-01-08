/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfortuna <mfortuna@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 12:17:55 by tbezerra          #+#    #+#             */
/*   Updated: 2025/01/08 14:52:23 by mfortuna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	open_out(t_data *data, char *name, enum e_type redir)
{
	int	fd;

	if (redir == R_AP)
		fd = open(name, O_CREAT | O_WRONLY | O_APPEND, 0644);
	else
		fd = open(name, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd < 0)
	{
		perror(name);
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
	close(fd);
	return (fd);
}

int	try_open_in(t_data *data, char *name)
{
	int	fd;

	fd = open(name, O_RDONLY);
	if (fd < 0)
	{
		perror(name);
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
	close(fd);
	return (fd);
}

void	ft_redir_all(t_data *data, t_cmd *cmd)
{
	t_files	*file;

	file = cmd->file;
	if (file == NULL)
		return ;
	while (file)
	{
		if (file->redir == R_HD)
			create_file(file, 0);
		else if (file->redir == R_IN)
			try_open_in(data, file->name);
		else if (file->redir == R_OUT || file->redir == R_AP)
			open_out(data, file->name, file->redir);
		file = file->next;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfortuna <mfortuna@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 20:13:10 by mfortuna          #+#    #+#             */
/*   Updated: 2025/01/20 20:03:47 by mfortuna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	create(char *name, char *hd_buffer, int fd, t_iter *x)
{
	while (access(name, F_OK) == 0)
		name[x->j++] = '3';
	fd = open(name, O_CREAT | O_RDWR | O_TRUNC, 0666);
	ft_fprintf(fd, 0, "%s", hd_buffer);
	close(fd);
	fd = open(name, O_RDONLY);
	if (dup2(fd, STDIN_FILENO) == -1)
		return (ft_fprintf(2, -1, "dup error\n"));
	close(fd);
	return (fd);
}

int	create_file(t_files *file, int fd)
{
	t_iter	*x;
	char	name[256];

	x = init_iter();
	if (!file->hd_buffer)
		return (-1);
	ft_memset(name, 0, 256);
	name[x->j++] = '.';
	while (file->name[x->i])
	{
		if (file->name[x->i] == 34 || file->name[x->i] == 39)
			x->i++;
		if (file->name[x->i] == 0)
			break ;
		name[x->j++] = file->name[x->i++];
	}
	fd = create(name, file->hd_buffer, fd, x);
	free(x);
	return (unlink(name), fd);
}

int	hd_errors(t_data *data, char *buffer_hd, int error)
{
	ft_heredoc_sig(-2);
	if (buffer_hd)
		free (buffer_hd);
	if (error == 1)
		return (ft_fprintf(2, 1, "MS: warning: here-document"
				" at line 1 delimited by end-of-file (wanted `here')\n"));
	if (error == 2)
	{
		data->check = 1;
		r_value(130, 1);
		return (89734);
	}
	return (3);
}

int	ft_heredoc_sig(int sig)
{
	static bool		end;	

	if (sig == SIGINT)
	{
		rl_done = 1;
		end = true;
	}
	if (sig == -2)
	{
		end = false;
		rl_event_hook = NULL;
		rl_done = 0;
	}
	if (end == true)
		return (1);
	return (0);
}

void	set_heredoc_signals(void)
{
	struct sigaction	sa;

	sigemptyset(&sa.sa_mask);
	sa.sa_handler = (void *)ft_heredoc_sig;
	sa.sa_flags = 0;
	sigaction(SIGINT, &sa, NULL);
	signal(SIGQUIT, SIG_IGN);
}

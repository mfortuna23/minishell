/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfortuna <mfortuna@student.42.pt>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 20:13:10 by mfortuna          #+#    #+#             */
/*   Updated: 2024/11/21 17:38:32 by mfortuna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	create_file(t_cmd *cmd, char *buffer)
{
	int		i;
	int		j;
	char	name[256];

	i = 0;
	j = 0;
	ft_memset(name, 0, 256);
	name[j++] = '.';
	while (cmd->infile[i])
	{
		if (cmd->infile[i] == 34)
			i++;
		name[j++] = cmd->infile[i++];
	}
	free(cmd->infile);
	cmd->infile = ft_strdup(name);
	cmd->fd_in = open(cmd->infile, O_CREAT | O_RDWR | O_TRUNC, 0666);
	ft_fprintf(cmd->fd_in, 0, "%s", buffer);
	printf("%s", buffer);
	close(cmd->fd_in);
}

int	hd_errors(t_data *data, char *buffer_hd, int error)
{
	if (buffer_hd)
		free (buffer_hd);
	if (error == 1) // ^D
		return (ft_fprintf(2, 1,"MS: warning: here-document"
			" at line 1 delimited by end-of-file (wanted `here')\n"));
	if (error == 2) // ^C
	{
		data->check = 1;
		data->return_v = 130;
		return (error);
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
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		ioctl(0, TIOCSTI, "");
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

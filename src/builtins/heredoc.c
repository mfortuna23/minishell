/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfortuna <mfortuna@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 13:24:59 by mfortuna          #+#    #+#             */
/*   Updated: 2025/01/15 00:05:42 by mfortuna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	event(void)
{
	return (0);
}

int	get_heredoc(t_data *data, t_files *infile, char *name, bool exp)
{
	char	*input;
	char	*buffer_hd;

	buffer_hd = ft_calloc(1, sizeof(char));
	set_heredoc_signals();
	while (1)
	{
		rl_event_hook = event;
		input = readline("heredoc> ");
		if (ft_heredoc_sig(-1) == 1)
			return (hd_errors(data, buffer_hd, 2));
		if (!input)
			return (hd_errors(data, buffer_hd, 1));
		if (ft_strncmp(input, name, ft_strlen(name) + 1) == 0)
			break ;
		buffer_hd = str_join(buffer_hd, ft_strdup_noquotes(data, input, \
		ft_calloc(256, sizeof(char)), exp));
		buffer_hd = str_join(buffer_hd, ft_strdup("\n"));
	}
	if (input)
		free(input);
	infile->hd_buffer = ft_strdup(buffer_hd);
	free(buffer_hd);
	set_up_sigaction();
	return (0);
}

int	here_doc(t_data *data, t_files *node, bool exp, int y) //TODO solve
{
	char	*here_doc;

	(void)y;
	if (node->name[0] == 34 || node->name[0] == 39)
	{
		exp = false;
		here_doc = ft_substr(node->name, 1, ft_strlen(node->name) - 2);
	}
	else
		here_doc = ft_substr(node->name, 0, ft_strlen(node->name));
	data->check = get_heredoc(data, node, here_doc, exp);
	ft_heredoc_sig(-2);
	free(here_doc);
	return (2);
}

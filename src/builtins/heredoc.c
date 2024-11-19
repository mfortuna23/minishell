/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfortuna <mfortuna@student.42.pt>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 13:24:59 by mfortuna          #+#    #+#             */
/*   Updated: 2024/11/19 13:43:51 by mfortuna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	create_file(t_cmd *cmd)
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
}

int	here_doc_w(t_data *data, t_cmd *cmd, char *name, bool exp)
{
	char	*input;

	data->i = 0;
	input = readline("heredoc> ");
	while (input)
	{
		if (ft_strncmp(input, name, ft_strlen(name) + 1) == 0)
			break ;
		while (input[data->i])
		{
			if (exp && input[data->i] == '$')
				data->i = print_var(data, input, ++data->i);
			else
				ft_fprintf(cmd->fd_in, 0, "%c", input[data->i++]);
		}
		ft_fprintf(cmd->fd_in, 0, "\n");
		free(input);
		input = readline("heredoc> ");
		data->i = 0;
	}
	if (!input)
		return (ft_fprintf(2, 1,"MS: warning: here-document"
			" at line 1 delimited by end-of-file (wanted `here')\n"));
	free(input);
	return (0);
}

int	here_doc(t_data *data, t_cmd *cmd, bool exp, int y)
{
	char	*here_doc;

	cmd->here_doc = true;
	if (!data->tokens[y])
		return (-9857);
	if (cmd->infile[0] == 34 || cmd->infile[0] == 39)
	{
		exp = false;
		here_doc = ft_substr(cmd->infile, 1, ft_strlen(cmd->infile) - 2);
	}
	else
		here_doc = ft_substr(cmd->infile, 0, ft_strlen(cmd->infile));
	create_file(cmd);
	here_doc_w(data, cmd, here_doc, exp);
	free(here_doc);
	close(cmd->fd_in);
	return (2);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfortuna <mfortuna@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 13:24:59 by mfortuna          #+#    #+#             */
/*   Updated: 2024/11/18 23:49:54 by mfortuna         ###   ########.fr       */
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

void	here_doc_w(t_data *data, t_cmd *cmd, char *name, bool exp)
{
	char	*input;
	int		i;

	i = 0;
	input = readline("heredoc> ");
	while (ft_strncmp(input, name, ft_strlen(name) + 1))
	{
		while (input[i])
		{
			if (exp && input[i] == '$')
				i = print_var(data, input, ++i);
			else
				ft_fprintf(cmd->fd_in, 0, "%c\n", input[i++]);
		}
		ft_fprintf(cmd->fd_in, 0, "\n");
		free(input);
		input = readline("heredoc> ");
		i = 0;
	}
	free(input);
}

int	here_doc(t_data *data, t_cmd *cmd, bool exp, int y)
{
	char	*here_doc;

	cmd->here_doc = true;
	if (!data->tokens[++y])
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
	close(cmd->fd_out);
	return (3);
}

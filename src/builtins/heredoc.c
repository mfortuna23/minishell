/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfortuna <mfortuna@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 13:24:59 by mfortuna          #+#    #+#             */
/*   Updated: 2024/11/20 22:27:28 by mfortuna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*w_var_buffer(t_data *data, char *input, char *buffer_hd)
{
	t_env	*var;
	char	name[256];
	char	*tmp;
	int		j;

	ft_memset(name, 0, 256);
	data->i++;
	tmp = NULL;
	j = 0;
	while ((input[data->i]) && input[data->i] != ' ')
		name[j++] = input[data->i++];
	var = find_var(data, name);
	if (!var)
		return (ft_strdup(""));
	data->i = data->i + (ft_strlen(name) - 1);
	tmp = str_join(buffer_hd, ft_strdup(var->value));
	return (tmp);
}

char	*w_buffer_hd(t_data *data, char *input, char *buffer_hd, bool exp)
{
	char	*tmp;

	tmp = NULL;
	while (input[data->i])
	{
		if (exp && input[data->i] == '$')
			buffer_hd = w_var_buffer(data, input, buffer_hd);
		else
			buffer_hd = str_join(buffer_hd, ft_substr(input, data->i, 1));
		if (data->i > ft_strlen(input))
			break ;
		data->i++;
	}
	tmp = str_join(buffer_hd, ft_strdup("\n"));
	return (tmp);
}

int	get_heredoc(t_data *data, t_cmd *cmd, char *name, bool exp)
{
	char	*input;
	char	*buffer_hd;

	buffer_hd = NULL;
	buffer_hd = ft_calloc(1, sizeof(char));
	set_heredoc_signals();
	rl_done = 0;
	while (1)
	{
		if (rl_done == 1)
			break ;
		input = readline("heredoc> ");
		if (!input)
			return (hd_errors(buffer_hd, 1));
		if (ft_strncmp(input, name, ft_strlen(name) + 1) == 0)
			break ;
		data->i = 0;
		buffer_hd = w_buffer_hd(data, input, buffer_hd, exp);
	}
	if (input)
		free(input);
	create_file(cmd, buffer_hd);
	free(buffer_hd);
	return (0);
}

int	here_doc(t_data *data, t_cmd *cmd, bool exp, int y)
{
	char	*here_doc;

	cmd->here_doc = true;
	(void)y;
	if (cmd->infile[0] == 34 || cmd->infile[0] == 39)
	{
		exp = false;
		here_doc = ft_substr(cmd->infile, 1, ft_strlen(cmd->infile) - 2);
	}
	else
		here_doc = ft_substr(cmd->infile, 0, ft_strlen(cmd->infile));
	data->check = get_heredoc(data, cmd, here_doc, exp);
	free(here_doc);
	return (2);
}

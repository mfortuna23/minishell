/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_cmds.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfortuna <mfortuna@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 10:42:34 by mfortuna          #+#    #+#             */
/*   Updated: 2025/01/15 00:41:24 by mfortuna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	syntax_error(t_data *data, char *error)
{
	r_value(2, 1);
	ft_fprintf(2, 0, error);
	data->check = 1;
	return (-983904);
}

int	ft_red_infile(t_data *data, t_cmd *c, int y, int x)
{
	while (data->tokens[y][x] == '<')
		x++;
	if (x > 2)
		return (syntax_error(data, \
		"MS: syntax error near unexpected token '<'\n"));
	if (!data->tokens[y + 1])
		return (syntax_error(data, \
		"MS: syntax error near unexpected token `newline'\n"));
	if (x == 1)
		add_last_file(data, &c->file, R_IN, data->tokens[++y]);
	if (x > 1)
	{
		add_last_file(data, &c->file, R_HD, data->tokens[++y]);
		return (here_doc(data, findlast_file(&c->file), true, y));
	}
	return (2);
}

int	ft_redirect(t_data *data, t_cmd *current, int y, int x)
{
	if (data->tokens[y][x] == '<')
		return (ft_red_infile(data, current, y, x));
	while (data->tokens[y][x] == '>')
		x++;
	if (x > 2)
		return (syntax_error(data, \
		"MS: syntax error near unexpected token '>'\n"));
	if (!data->tokens[++y])
		return (syntax_error(data, \
		"MS: syntax error near unexpected token `newline'\n"));
	if (x > 1)
		add_last_file(data, &current->file, R_AP, data->tokens[y]);
	else
		add_last_file(data, &current->file, R_OUT, data->tokens[y]);
	return (2);
}

int	ft_cmd_args(t_data *data, t_cmd *node, int y, int x)
{
	while ((data->tokens[y]) && (check_chars(data->tokens[y][x]) == 0))
	{
		node->cmd[data->i] = ft_strdup_noquotes(data, \
			data->tokens[y++], ft_calloc(256, sizeof(char)), true);
		if (node->cmd[data->i] != NULL)
			data->i++;
	}
	return (y);
}

char	*get_var_name(char *str) // check for ?
{
	int		i;
	char	*name;

	i = 0;
	if (str[i] == '?')
		return (ft_strdup("?"));
	while (str[i] && valid_varchars(str[i]) == 0)
		i++;
	if (i == 0)
		return (NULL);
	name = ft_substr(str, 0, i);
	return (name);
}

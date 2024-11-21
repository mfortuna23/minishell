/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_cmds.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfortuna <mfortuna@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 10:42:34 by mfortuna          #+#    #+#             */
/*   Updated: 2024/11/21 22:24:00 by mfortuna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_red_infile(t_data *data, t_cmd *current, int y, int x)
{
	if (current->infile)
		free(current->infile);
	while (data->tokens[y][x] == '<')
		x++;
	if (x > 2)
		return (ft_fprintf(2, -1, "parser error near : '<'"));
	if (!data->tokens[y + 1])
		return (ft_fprintf(2, -36842, \
		"MS: syntax error near unexpected token `newline'\n"));
	current->infile = ft_strdup(data->tokens[++y]);
	if (x > 1)
		return (here_doc(data, current, true, y));
	return (2);
}

int	ft_redirect(t_data *data, t_cmd *current, int y, int x)
{
	if (data->tokens[y][x] == '<')
		return (ft_red_infile(data, current, y, x));
	if (current->outfile)
		free(current->outfile);
	while (data->tokens[y][x] == '>')
		x++;
	if (x > 2)
		return (ft_fprintf(2, -1654, "parser error near : '>'\n"));
	else if (x > 1)
		current->appen = true;
	if (!data->tokens[++y])
		return (ft_fprintf(2, -36842, \
		"MS: syntax error near unexpected token `newline'\n"));
	current->outfile = ft_strdup(data->tokens[y]);
	return (2);
}

int	ft_cmd_args(t_data *data, t_cmd *node, int y, int x)
{
	int		count;
	t_env	*var;

	var = NULL;
	data->i = y;
	while ((data->tokens[data->i]) && (check_chars(data->tokens[data->i][x]) == 0))
		data->i++;
	count = data->i - y;
	node->cmd = malloc((count + 1) * sizeof(char *));
	data->i = 0;
	while ((data->tokens[y]) && check_chars(data->tokens[y][x]) == 0)
	{
		if (data->tokens[y][0] == '$')// FIX THIS AAAAAAH
		{
			var = find_var(data, data->tokens[y] + 1);
			if (var)
			{
				node->cmd[data->i++] = ft_strdup(var->value);
				y++;
			}
		}
		node->cmd[data->i++] = ft_strdup(data->tokens[y++]);
	}
	node->cmd[data->i] = 0;
	return (y);
}

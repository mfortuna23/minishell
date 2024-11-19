/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_cmds.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfortuna <mfortuna@student.42.pt>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 10:42:34 by mfortuna          #+#    #+#             */
/*   Updated: 2024/11/19 11:15:41 by mfortuna         ###   ########.fr       */
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
		return (ft_fprintf(3, -36842, \
		"MS: syntax error near unexpected token `newline'"));
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
		return (ft_fprintf(2, -1654, "parser error near : '>'"));
	else if (x > 1)
		current->appen = true;
	if (!data->tokens[++y])
		return (-1123);
	current->outfile = ft_strdup(data->tokens[y]);
	return (2);
}

int	ft_cmd_args(t_data *data, t_cmd *node, int y, int x)
{
	int	count;
	int	i;

	i = y;
	while ((data->tokens[i]) && (check_chars(data->tokens[i][x]) == 0))
		i++;
	count = i - y;
	node->cmd = malloc((count + 1) * sizeof(char *));
	i = 0;
	while ((data->tokens[y]) && check_chars(data->tokens[y][x]) == 0)
		node->cmd[i++] = ft_strdup(data->tokens[y++]);
	node->cmd[i] = 0;
	return (y);
}

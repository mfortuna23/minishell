/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_cmds.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfortuna <mfortuna@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 10:42:34 by mfortuna          #+#    #+#             */
/*   Updated: 2024/11/28 16:31:23 by mfortuna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char *ft_strdup_noquotes(t_data *data, char *old, char *new, bool exp);

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

// TODO expand name of file exept for heredoc ihmfl
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

int	get_var(t_data *data, t_cmd *node, int y)
{
	t_env	*var;

	var = NULL;
	var = find_var(data, data->tokens[y] + 1);
	if (var)
	{
		node->cmd[data->i++] = ft_strdup(var->value);
		return (++y);
	}
	else if (data->tokens[y][1] == 0)
	{
		node->cmd[data->i++] = ft_strdup(data->tokens[y++]);
		return (y);
	}
	else if (data->tokens[y][1] == '?')
	{
		node->cmd[data->i++] = ft_strdup(ft_itoa(r_value(0, 0)));
		return (++y);
	}
	node->cmd[data->i++] = ft_strdup(data->tokens[y++]);
	return (y);
}

int	ft_cmd_args(t_data *data, t_cmd *node, int y, int x)
{
	int		count;
	int		i;

	i = y;
	while ((data->tokens[i]) && \
	(check_chars(data->tokens[i][x]) == 0))
		i++;
	count = i - y;
	node->cmd = ft_calloc((count + 1), sizeof(char *));
	while ((data->tokens[y]) && (check_chars(data->tokens[y][x]) == 0) \
	&& (data->i < count))
		node->cmd[data->i++] = ft_strdup_noquotes(data, \
			data->tokens[y++], ft_calloc(256, sizeof(char)), true);
	return (y);
}

char	*get_var_name(char *str) // check for ?
{
	int		i;
	char	*name;

	i = 0;
	while (str[i] && str[i] > 32 && str[i] != 34 && str[i] != '$')
		i++;
	if (i == 0)
		return (NULL);
	name = ft_substr(str, 0, i);
	return (name);
}

void	init_iter(t_iter *iter)
{
	iter->c = 'a';
	iter->i = 0;
	iter->j = 0;
}

bool	true_false(bool exp)
{
	if (exp == false)
		return (true);
	return (false);
}

void	w_var_inbuffer(t_data *data, char *old, char *new, t_iter *x)
{
	t_env	*var;
	char	*name;
	int		i;

	x->i++;
	i = 0;
	name = get_var_name(old + x->i);
	if (!name)
	{
		new[x->j++] = '$';
		return ;
	}
	var = find_var(data, name);
	x->i += ft_strlen(name);
	free(name);
	if (!var)
		return ;
	while (var->value[i])
		new[x->j++] = var->value[i++];
}

//allocate memory in new before calling this function
char *ft_strdup_noquotes(t_data *data, char *old, char *new, bool exp)
{
	t_iter	x;

	init_iter(&x);
	while (old[x.i])
	{
		x.c = old[x.i];
		if (x.c == '$' && exp == true)
		{
			w_var_inbuffer(data, old, new, &x);
			while (new[++x.j]);
		}
		else if (x.c == 34 || x.c == 39)
		{
			x.i++;
			if (x.c == 39)
				exp = true_false(exp);
		}
		else
			new[x.j++] = old[x.i++];
	}
	return (new);
}

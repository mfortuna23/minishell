/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_cmds.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfortuna <mfortuna@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 10:42:34 by mfortuna          #+#    #+#             */
/*   Updated: 2024/12/11 13:28:22 by mfortuna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*ft_strdup_noquotes(t_data *data, char *old, char *new, bool exp);

int	ft_red_infile(t_data *data, t_cmd *current, int y, int x)
{
	while (data->tokens[y][x] == '<')
		x++;
	if (x > 2)
		return (ft_fprintf(2, -19876, "MS: syntax error near unexpected token '<'\n"));
	if (!data->tokens[y + 1])
		return (ft_fprintf(2, -36842, \
		"MS: syntax error near unexpected token `newline'\n"));
	if (x == 1)
		add_last_infile(data, &current->in_file, false, data->tokens[++y]);
	if (x > 1)
	{
		add_last_infile(data, &current->in_file, true, data->tokens[++y]);
		return (here_doc(data, current->in_file, true, y));
	}
	return (2);
}

// TODO expand name of file exept for heredoc ihmfl
int	ft_redirect(t_data *data, t_cmd *current, int y, int x)
{
	if (data->tokens[y][x] == '<')
		return (ft_red_infile(data, current, y, x));
	while (data->tokens[y][x] == '>')
		x++;
	if (x > 2)
		return (ft_fprintf(2, -1654, \
		"MS: syntax error near unexpected token '>'\n"));
	if (!data->tokens[++y])
		return (ft_fprintf(2, -36842, \
		"MS: syntax error near unexpected token `newline'\n"));
	if (x > 1)
		add_last_outfile(data, &current->out_file, true, data->tokens[y]);
	else
		add_last_outfile(data, &current->out_file, false, data->tokens[y]);
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
	while ((data->tokens[y]) && (check_chars(data->tokens[y][x]) == 0))
		node->cmd[data->i++] = ft_strdup_noquotes(data, \
			data->tokens[y++], ft_calloc(256, sizeof(char)), true);
	return (y);
}

char	*get_var_name(char *str) // check for ?
{
	int		i;
	char	*name;

	i = 0;
	if (str[i] == '?')
		return (ft_strdup("?"));
	while (str[i] && str[i] > 32 && str[i] != 34 && str[i] != '$')
		i++;
	if (i == 0)
		return (NULL);
	name = ft_substr(str, 0, i);
	return (name);
}

//create and init iter struct
t_iter	*init_iter(void)
{
	t_iter	*iter;

	iter = malloc(1 * sizeof(t_iter));
	iter->c = 0;
	iter->i = 0;
	iter->j = 0;
	iter->x = 0;
	iter->y = 0;
	return (iter);
}

bool	true_false(bool exp)
{
	if (exp == false)
		return (true);
	return (false);
}

void	w_nbr(int nbr, char *new, t_iter *x)
{
	char	*str;
	int		i;

	i = 0;
	str = ft_itoa(nbr);
	while (str[i])
		new[x->j++] = str[i++];
	free(str);
	
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
	if (ft_strncmp(name, "?\0", 2) == 0)
		w_nbr(r_value(0, 0), new, x);
	free(name);
	if (!var)
		return ;
	while (var->value[i])
		new[x->j++] = var->value[i++];
}

//allocate memory in new before calling this function
char *ft_strdup_noquotes(t_data *data, char *old, char *new, bool exp)
{
	t_iter	*x;

	x = init_iter();
	while (old[x->i])
	{
		x->c = old[x->i];
		if (x->c == '$' && exp == true)
		{
			w_var_inbuffer(data, old, new, x);
			while (new[++x->j]);
		}
		else if (x->c == 34 || x->c == 39)
		{
			x->i++;
			if (x->c == 39)
				exp = true_false(exp);
		}
		else
			new[x->j++] = old[x->i++];
	}
	free(x);
	return (new);
}

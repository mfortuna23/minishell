/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_cmds.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfortuna <mfortuna@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 10:42:34 by mfortuna          #+#    #+#             */
/*   Updated: 2025/01/08 14:02:24 by mfortuna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*ft_strdup_noquotes(t_data *data, char *old, char *new, bool exp);

int	syntax_error(t_data *data, char *error)
{
	r_value(2, 1);
	//printf("char error, parser error 2\n"); // TODO remove
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
		node->cmd[data->i++] = ft_strdup_noquotes(data, \
			data->tokens[y++], ft_calloc(256, sizeof(char)), true);
	return (y);
}

//if is valid return 0
int	valid_varchars(char c)
{
	if (ft_isalnum(c) == 1 || c == '_')
		return (0);
	return (1);
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
	iter->exp = true;
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
	//printf ("the PID is :%i\n", getpid()); TODO remove
	if (ft_strncmp(name, "?\0", 2) == 0)
		w_nbr(data->return_v, new, x);
	free(name);
	if (!var)
		return ;
	while (var->value[i])
		new[x->j++] = var->value[i++];
}

void	strdup_nq(t_data *data, char *old, char *new, t_iter *x)
{
	x->i++;
	if (old[x->i] != x->c)
	{
		printf("im in !!!! \n");
		if (x->c == 39)
			x->exp = true_false(x->exp);
		while (old[x->i] && old[x->i] != x->c)
		{
			if (old[x->i] == '$' && x->exp == true)
				w_var_inbuffer(data, old, new, x);
			else
				new[x->j++] = old[x->i++];
		//printf("%i\n", x->i - 1);
		}
	}
	else
		x->i++;
}

//allocate memory in new before calling this function
char	*ft_strdup_noquotes(t_data *data, char *old, char *new, bool exp)// TODO solve
{
	t_iter	*x;

	x = init_iter();
	x->exp = exp;
	while (old[x->i])
	{
		x->c = old[x->i];
		if (old[x->i] == '$' && x->exp == true)
			w_var_inbuffer(data, old, new, x);
		else if (old[x->i] == 34 || old[x->i] == 39)
			strdup_nq(data, old, new, x);
		else
			new[x->j++] = old[x->i++];
	}
	free(x);
	return (new);
}

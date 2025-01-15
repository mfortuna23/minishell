/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strdup_noq.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfortuna <mfortuna@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 00:40:50 by mfortuna          #+#    #+#             */
/*   Updated: 2025/01/15 00:41:46 by mfortuna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
		w_nbr(data->return_v, new, x);
	free(name);
	if (!var)
		return ;
	while (var->value[i])
		new[x->j++] = var->value[i++];
}

void	strdup_nq(t_data *data, char *old, char *new, t_iter *x)
{
	bool	exp;

	exp = x->exp;
	x->i++;
	if (old[x->i] != x->c)
	{
		if (x->c == 39)
			x->exp = true_false(x->exp);
		while (old[x->i] && old[x->i] != x->c)
		{
			if (old[x->i] == '$' && x->exp == true && exp == true)
				w_var_inbuffer(data, old, new, x);
			else
				new[x->j++] = old[x->i++];
		}
	}
	else
		x->i++;
}

//allocate memory in new before calling this function
char	*ft_strdup_noquotes(t_data *data, char *old, char *new, bool exp)
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
	if (x->j == 0 && old[0] == '$')
	{
		free(new);
		free(x);
		return (NULL);
	}
	free(x);
	return (new);
}

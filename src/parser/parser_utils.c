/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfortuna <mfortuna@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 10:14:09 by mfortuna          #+#    #+#             */
/*   Updated: 2025/01/27 10:09:44 by mfortuna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/* check for special chars not required by the subject 
also duplicated special chars*/
int	check_not_req(t_data *data)
{
	int	i;

	i = 0;
	if (!data || !data->tokens || !data->tokens[i])
		return (1);
	while (data->tokens[i])
	{
		if (check_chars(data->tokens[i][0]) == 2)
			return (ft_fprintf(2, 1, "MS: syntax error near unexpected"
					" token '%c'\n", data->tokens[i][0]));
		if (check_chars(data->tokens[i][0]) == 1 && (data->tokens[i + 1]) \
		&& (data->tokens[i + 1][0] == data->tokens[i][0] || \
		data->tokens[i + 1][0] == '|'))
			return (ft_fprintf(2, 1, "MS: syntax error near unexpected"
					" token '%c'\n", data->tokens[i + 1][0]));
		if ((data->tokens[i][0]) == '|' && (data->tokens[i][1]) == '|')
			return (ft_fprintf(2, 1, "MS: syntax error near unexpected "
					"token '%c'\n", data->tokens[i][0]));
		i++;
	}
	return (0);
}

int	token_count(char *s, int i, int count, char c)
{
	while (s[i])
	{
		while (s[i] <= ' ' && (s[i]))
			i++;
		if (s[i] > ' ' && s[i])
		{
			c = s[i++];
			count ++;
			if (c == 34 || c == 39)
			{
				while (c != s[i] && (s[i]))
					i++;
				if (s[i] == 0)
					return (count);
			}
			while (s[i] > ' ')
				i++;
		}
	}
	return (count);
}

/* fill data->parser */
void	less_space(t_data *data, char *arr, int i, int count)
{
	char	c;

	while (arr[i])
	{
		while (arr[i] > ' ' && (arr[i]))
		{
			c = arr[i];
			if ((arr[i]) && (c == 34 || c == 36))
			{
				while ((arr[i]) && arr[i] != c)
					data->parser[count++] = arr[i++];
			}
			if (arr[i] == '|')
			{
				data->parser[count++] = arr[i++];
				data->parser[count++] = ' ';
				break ;
			}
			if (arr[i])
				data->parser[count++] = arr[i++];
		}
		if (arr[i])
			data->parser[count++] = arr[i++];
	}
	data->parser[count] = 0;
}

int	token_create(t_data *d, t_iter *x)
{
	x->c = d->parser[x->i++];
	while (d->parser[x->i] && (d->parser[x->i++] != x->c))
		;
	if (d->parser[x->i] < 33)
		d->tokens[x->x++] = ft_substr(d->parser, x->j, x->i - x->j);
	else
		return (1);
	return (0);
}

int	split_tokens(t_data *d, t_iter *x)
{
	while (d->parser[x->i] && (x->x < d->n_tokens))
	{
		while (d->parser[x->i] <= ' ')
			x->i++;
		if (d->parser[x->i] > ' ')
		{
			x->j = x->i;
			while (d->parser[x->i] > ' ')
			{
				if ((d->parser[x->i] == 34 || d->parser[x->i] == 39))
				{
					if (token_create(d, x) == 1)
						continue ;
					else
						break ;
				}
				if ((d->parser[++x->i] <= ' ' || \
				d->parser[x->i] == 0) && (x->x < d->n_tokens))
					d->tokens[x->x++] = ft_substr(d->parser, x->j, x->i - x->j);
			}
		}
	}
	free(x);
	return (0);
}

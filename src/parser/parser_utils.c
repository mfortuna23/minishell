/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfortuna <mfortuna@student.42.pt>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 10:14:09 by mfortuna          #+#    #+#             */
/*   Updated: 2024/10/28 11:02:16 by mfortuna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int check_chars(char c)
{
	if (c == '|' || c == '<' || c == '>' )
		return (1);
	if (c == '&' || c == ';' || c == '\\')
		return (2);
	return (0);
}

int token_count(char *s, int i, int count, char c)
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
				while (c != s[i] && (s[i++]));
				if (s[i] == 0)
					return (-1);
			}
			while (s[i] > ' ')
				i++;
		}
	}
	return (count);
}
/* fill data->parser */
int less_space(t_data *data, char *arr, int i, int count)
{
	while (arr[i])
	{
		while (arr[i] <= ' ' && (arr[i]))
			i++;
		while (arr[i] > ' ')
		{
			if (arr[i] == '|')
			{
				while (arr[i] == '|')
				{
					data->parser[count++] = arr[i++];
					while (arr[i] == ' ')
						i++;
				}
				data->parser[count++] = ' ';
			}
			if (arr[i])
				data->parser[count++] = arr[i++];
		}
		if (arr[i])
			data->parser[count++] = arr[i++];
	}
	data->parser[count] = 0;
	return (0);
}
/* count necessary chars for data->parser */

int	split_tokens(t_data *data, int x, int i, int j)
{
	data->n_tokens = token_count(data->parser, 0, 0, 0);
	data->tokens = ft_calloc((data->n_tokens + 1), sizeof(char*));
	while (data->parser[i] && (x < data->n_tokens))
	{
		while (data->parser[i] <= ' ')
			i++;
		if (data->parser[i] > ' ')
		{
			j = i;
			while (data->parser[i] > ' ')
			{
				if ((data->parser[i] == 34 || data->parser[i] == 39) && j == i)
				{
					while ((data->parser[++i] != data->parser[j]) && data->parser[i]);
					if (data->parser[i++] == 0)
						return (1);
					data->tokens[x++] = ft_substr(data->parser, j, (i - j));
					break ;
				}
				if ((data->parser[++i] <= ' ' || data->parser[i] == 0) && (x < data->n_tokens))
					data->tokens[x++] = ft_substr(data->parser, j, (i - j));
			}
		}
	}
	return (0);
}

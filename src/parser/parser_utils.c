/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfortuna <mfortuna@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 10:14:09 by mfortuna          #+#    #+#             */
/*   Updated: 2024/11/28 16:27:36 by mfortuna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/* check for special chars not required by the subject also duplicated special chars*/
int	check_not_req(t_data *data)
{
	int	i;

	i = 0;
	while (data->tokens[i])
		printf("...%s...\n", data->tokens[i++]);
	i = 0;
	while (data->tokens[i])
	{
		if (check_chars(data->tokens[i][0]) == 2)
			return (ft_fprintf(2, 1, "MS: syntax error near unexpected"
					" token '%c'\n", data->tokens[i][0]));
		if (check_chars(data->tokens[i][0]) == 1 && (data->tokens[i + 1]) \
		&& check_chars(data->tokens[i + 1][0]) == 1)
			return (ft_fprintf(2, 1, "MS: syntax error near unexpected"
					" token '%c'\n", data->tokens[i + 1][0]));
		if ((data->tokens[i][0]) == '|' && (data->tokens[i][1]) == '|')
			return (ft_fprintf(2, 1, "bash: syntax error near unexpected "
					"token '%c'\n", data->tokens[i][0]));
		i++;
	}
	return (0);
}

int	check_chars(char c)
{
	if (c == '|' || c == '<' || c == '>' )
		return (1);
	if (c == '&' || c == ';' || c == '\\')
		return (2);
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
					return (-1);
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


int	split_tokens(t_data *data, int x, int i, int j)
{
	while (data->parser[i] && (x < data->n_tokens))
	{
		while (data->parser[i] <= ' ')
			i++;
		if (data->parser[i] > ' ')
		{
			j = i;
			while (data->parser[i] > ' ')
			{
				if ((data->parser[i] == 34 || data->parser[i] == 39))
				{
					while ((data->parser[++i] != data->parser[j]) \
					&& data->parser[i]);
					data->tokens[x++] = ft_substr(data->parser, j, (i - j));
					break ;
				}
				if ((data->parser[++i] <= ' ' || \
				data->parser[i] == 0) && (x < data->n_tokens))
					data->tokens[x++] = ft_substr(data->parser, j, (i - j));
			}
		}
	}
	return (0);
}

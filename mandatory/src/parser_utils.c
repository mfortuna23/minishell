/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfortuna <mfortuna@student.42.pt>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 10:14:09 by mfortuna          #+#    #+#             */
/*   Updated: 2024/10/02 11:36:53 by mfortuna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int check_chars(char c)
{
	if (c == '|' || c == '<' || c == '>')
		return (1);
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
int less_space(t_data *data, char *arr, int i)
{
	int count;

	count = 0;
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
			data->parser[count++] = arr[i++];
		}
		data->parser[count++] = arr[i++];
	}
	return (0);
}
/* count necessary chars for data->parser */
int	skip_spaces(t_data *data, char *arr, int i, int count)
{
	while (arr[i])
	{
		while (arr[i] <= ' ' && (arr[i]))
			i++;
		while (arr[i] > ' ')
		{
			count ++;
			while (arr[i] == '|' || arr[i] == ' ')
			{
				if (arr[i] == '|')
				{
					i++;
					count++;
				}
				else
					i++;
			}
			i++;
		}
		count ++;
	}
	data->parser = ft_calloc(count + 1, sizeof(char));
	less_space(data, arr, 0);
	return (0);
}

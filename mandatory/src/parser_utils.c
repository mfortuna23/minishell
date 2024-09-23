/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfortuna <mfortuna@student.42.pt>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 10:14:09 by mfortuna          #+#    #+#             */
/*   Updated: 2024/09/23 17:11:22 by mfortuna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int token_count_two(char *s, int i)
{
	int words;

	words = 0;
	while ((s[i] > ' ') && s[i])
	{
		if (s[i] == '|')
		{
			words ++;
			i++;
			if (s[i] > ' ')
			{
				while (s[i] == '|' || s[i] == ' ')
					i++;
				words++;
				i--;
			}
		}
		i++;
	}
	if (words > 2)
		return (2);
	return (1);
}

int word_end (char *s, int i)
{
	while (s[i] > ' ')
	{
		if (s[i] == '|')
		{
			printf("stopped at '%c'\n", s[i]);
			return (i);
		}
		i++;
	}
	printf("stopped at '%c'\n", s[i]);
	return (i);
}

int count_pipe (char *s, int i)
{
	int j;

	j = i;
	while (s[i] > ' ')
	{
		if (s[i] == '|')
		{
			if (j == i)
				return (0);
			return (1);
		}
		i++;
	}
	return (0);
}

int	token_count(char *s, int i, int j, int words)
{
	while (s[i])
	{
		while ((s[i] <= ' ') && s[i])
			i++;
		if (s[i] > ' ')
		{
			words ++;
			if (s[i] == 34 || s[i] == 39)
			{
				j = i;
				while ((s[++i] != s[j]) && s[i]);
			}
			if ((s[i] > ' ') && s[i])
			{
				words+= count_pipe(s, i);
				i = word_end(s, i);
			}
			if (s[i] == '|')
			{
				while (s[i] == '|' || s[i] == ' ')
					i++;
			}
		}
	}
	return (words);
}

char	*get_quotes(char *s, int i, int j)
{
	while ((s[i] != s[j]) && s[i])
		i++;
	return (ft_substr(s, j, (i - j) + 1));
}

char	*get_word(char *s, int i, int j)
{
	if (s[i] == '|')
		return (ft_substr(s, i, 1));
	while (s[i] <= ' ' && s[i])
		i++;
	if (s[i] > ' ' && s[i])
	{
		if (s[i] == 34 || s[i] == 39)
			return (get_quotes(s, i + 1, i));
		j = i;
		while (s[i] > ' ')
		{
			i++;
			if (s[i] <= ' ' || s[i] == 0 || s[i] == '|')
			{
				if (s[i] == '|')
					return (ft_substr(s, j, (i - j)));
				return (ft_substr(s, j, (i - j) + 1));
			}
		}
	}
	return (NULL);
}
/* falta verificar se o file n\ao esta junto com '<' aaaaaaaaaaaaaaaaaaaaaaaaaaaaaah */
int	ft_strtok(t_data *data)
{
	int		i;
	int		x;
	int		words;

	words = token_count(data->input, 0, 0, 0);
	if (words < 1)
		return (1);
	data->tokens = ft_calloc((words + 1), sizeof(char *));
	i = 0;
	data->tokens[0] = get_word(data->input, 0, 0);
	x = 1;
	while (x < words && data->input[i])
	{
		while (data->input[i] == '|' || data->input[i] == ' ')
			i++;
		if (data->tokens[x - 1][0] != '|')
			i += ft_strlen(data->tokens[x - 1]);
		while (data->input[i] <= ' ')
			i++;
		data->tokens[x] = get_word(data->input, i, 0);
		x++;
	}
	if (data->tokens[x] == NULL)
		free(data->tokens[x]);
	return (0);
}

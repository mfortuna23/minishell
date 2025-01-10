/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   full_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfortuna <mfortuna@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 10:38:42 by mfortuna          #+#    #+#             */
/*   Updated: 2025/01/09 10:20:01 by mfortuna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_errorfullinput(t_data *data)
{
	data->check = 1;
	free(data->input);
	r_value(130, 1);
	set_up_sigaction();
	ft_heredoc_sig(-2);
	return (1);
}

int	get_quotes2(t_data *data)
{
	char	*new;

	new = NULL;
	new = readline("quote> ");
	if (ft_heredoc_sig(-1) == 1 || !new)
		return (ft_errorfullinput(data));
	data->input = str_join(data->input, new);
	return (0);
}

int	get_quotes(t_data *data, int i, char c, int check)
{
	while (data->input[i])
	{
		if (data->input[i] == 34 || data->input[i] == 39)
		{
			c = data->input[i++];
			while (data->input[i] != c)
			{
				if (data->input[i] == 0)
				{
					ft_fprintf(2, 1, "MS: syntax error expected '%c'\n", c);
					r_value(158, 1);
					data->check = 1;
					return(1);
				}
				else
					i++;
			}
		}
		i++;
	}
	return (check);
}

//find s2 in s1 1 not found
int	find_str(char *s1, char *s2, int tmp)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (!s1 || !s2)
		return (1);
	if (ft_strlen(s2) > ft_strlen(s1))
		return (1);
	while (s1[i])
	{
		while (s1[i] == s2[j])
		{
			i++;
			j++;
			if (s2[j] == '\0')
				return (0);
		}
		j = 0;
		tmp ++;
		i = tmp;
	}
	return (1);
}

int	get_pipes(t_data *data, int i, int check)
{
	char	*new;

	new = NULL;
	while ((i >= 0) && (data->input[i] == '|' || data->input[i] == ' '))
	{
		if ((i >= 0) && data->input[i] == ' ')
			i--;
		else
		{
			check = -1;
			if (find_str(data->input, "<|", 0) || find_str(data->input, \
			">|", 0) || ft_strnstr(data->input, "|", 1))
				return (parasing_error(data, 1));
			new = readline("pipe> ");
			if (ft_heredoc_sig(-1) == 1 || !new)
				return (ft_errorfullinput(data));
			data->input = str_join(data->input, new);
			i = ft_strlen(data->input) - 1;
		}
	}
	return (check);
}

int	get_fullinput(t_data *data)
{
	int	q;
	int	p;
	int	i;

	q = -1;
	p = -1;
	i = 0;
	set_heredoc_signals();
	ft_heredoc_sig(-2);
	while (data->input[i] && data->input[i] <= 32)
		i++;
	if (data->input[i] == 0)
		return (data_check(data, 1, 1));
	while (p == -1 || q == -1)
	{
		q = get_quotes(data, 0, 'a', 0);
		if (q == 1)
			return (1);
		p = get_pipes(data, ft_strlen(data->input) - 1, 0);
		if (p == 1)
			return (1);
	}
	ft_heredoc_sig(-2);
	set_up_sigaction();
	return (0);
}

int	data_check(t_data *data, int check, int r_value)
{
	data->check = check;
	return (r_value);
}

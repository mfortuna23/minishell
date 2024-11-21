/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   full_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfortuna <mfortuna@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 10:38:42 by mfortuna          #+#    #+#             */
/*   Updated: 2024/11/21 22:16:16 by mfortuna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	get_quotes(t_data *data, int i)
{
	char	c;
	int		check;

	check = 0;
	while (data->input[i])
	{
		if (data->input[i] == 34 || data->input[i] == 39)
		{
			c = data->input[i];
			i++;
			while (data->input[i] != c)
			{
				if (data->input[i] == 0)
				{
					check = -1;
					data->input = str_join(data->input, readline("quote> "));
				}
				else
					i++;
			}
		}
		i++;
	}
	return (check);
}

int	get_pipes(t_data *data, int i)
{
	int	check;

	check = 0;
	while (data->input[i] == '|' || data->input[i] == ' ')
	{
		if (data->input[i] == ' ')
			i--;
		else
		{
			check = -1;
			if (ft_strnstr(data->input, "<|", 100) || ft_strnstr(data->input, \
			">|", 100) || ft_strnstr(data->input, "|", 1))
				return (parasing_error(data, 1));
			data->input = str_join(data->input, readline("pipe> "));
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
	while (data->input[i] && data->input[i] <= 32)
		i++;
	if (data->input[i] == 0)
		return (data_check(data, 1, 1));
	while (p == -1 || q == -1)
	{
		q = get_quotes(data, 0);
		p = get_pipes(data, ft_strlen(data->input) - 1);
		if (p == 1)
			return (data_check(data, 1, 1));
	}
	return (0);
}

int	data_check(t_data *data, int check, int r_value)
{
	data->check = check;
	return (r_value);
}

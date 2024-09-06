/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfortuna <mfortuna@student.42.pt>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 11:27:08 by mfortuna          #+#    #+#             */
/*   Updated: 2024/09/06 11:11:02 by mfortuna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void count_cmds(t_data *data)
{
	int i;

	i = 0;
	data->n_cmd = 1;
	while(data->input[i])
	{
		if (data->input[i] == '|')
			data->n_cmd++;
		i++;
	}
}
int	handle_str(t_data *data, char *input)
{
	int i;
	int j;

	i = 1;
	j = 0;
	while (input[i])
	{
		while (input[i] != input[j])
			i++;
		return (i);
	}
	return (-1);
}

int	handle_less(t_data *data, char *input, t_cmd *current)
{
	int i;
	int	j;

	j = 0;
	i = 0;
	while (input[i])
	{
		if (input[i] == '<')
			return (ft_printf("idk how to handle '<<' \n"));
		while (input[i] <= ' ')
			i++;
		while (data->input[i] > ' ')
		{
			if (data->input[i] == 34 || data->input[i] == 39)
			{
				j = i;
				i = handle(data, input + i);
			}
			if (current->infile == NULL)
				current->infile = ft_substr(input, j, i - j);
			else
				current->cmd = ft_substr(input, j, i - j);
		}
		i++;
	}
}

int	input_user(t_data *data)
{
	int	i;
	t_cmd *current;

	i = 0;
	data->cmd = create_cmds(data->n_cmd);
	current = (*data->cmd);
	while (data->input[i])
	{
		while (data->input[i] <= ' ')
			i++;
		if (data->input[i] == '<')
			i = handle_less(data, data->input + i + 1, current);
	}
}


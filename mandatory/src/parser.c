/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfortuna <mfortuna@student.42.pt>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 11:27:08 by mfortuna          #+#    #+#             */
/*   Updated: 2024/09/05 15:11:53 by mfortuna         ###   ########.fr       */
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

int	handle_less(t_data *data, char *imput)
{
	int i;

	i = 0;
	while (imput[i])
	{
		if (data->input[i] == '<')
			return (ft_printf("idk how to handle << \n"));
	}
	
}

int	input_user(t_data *data)
{
	int	i;

	i = 0;
	data->cmd = create_cmds(data->n_cmd);
	while (data->input[i])
	{
		while(data->input[i] <= ' ')
			i++;
		if (data->input[i] == '<')
			return(handle_less(data, data->input + i + 1));
	}
}


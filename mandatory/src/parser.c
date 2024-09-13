/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfortuna <mfortuna@student.42.pt>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 11:27:08 by mfortuna          #+#    #+#             */
/*   Updated: 2024/09/13 12:26:27 by mfortuna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int divide_cmds(t_data *data)
{
	
}

int define_cmds(t_data *data, t_cmd *current)
{
	int	cmds;
	int	i;
	
	cmds = 1;
	i = 0;
	if (data->n_cmd == 1)
	{
		current->full_cmd = data->tokens;
		return (0);
	}
	while (i < data->n_cmd)
	{
		while (data->tokens[i][0] != '|' && data->tokens[i])
			i ++;
		if (data->tokens[i][0] == '|')
		{
			
		}
	}
}

int	input_user(t_data *data)
{
	int		i;
	t_cmd	*current;

	i = 0;
	current = (*data->cmd);
	count_cmds(data);
	data->cmd = create_cmds(data->n_cmd);
	data->tokens = split_cmd(data->input);
	define_cmds(data);
}


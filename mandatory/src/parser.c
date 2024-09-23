/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfortuna <mfortuna@student.42.pt>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 11:27:08 by mfortuna          #+#    #+#             */
/*   Updated: 2024/09/23 15:22:18 by mfortuna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int divide_cmds(t_data *data)
{
	
}
/* define each cmd */
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
/* recives and manages input from user */
int	input_user(t_data *data)
{
	int		i;
	t_cmd	*current;

	i = 0;
	current = (*data->cmd);
	count_cmds(data);
	data->cmd = create_cmds(data->n_cmd);
	data->tokens = ft_strtok(data);
	define_cmds(data, current);
}


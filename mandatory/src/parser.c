/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfortuna <mfortuna@student.42.pt>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 11:27:08 by mfortuna          #+#    #+#             */
/*   Updated: 2024/09/12 13:29:05 by mfortuna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int divide_cmds(t_data *data)
{
	
}

int define_cmds(t_data *data)
{
	int	i;
	int	token;
	
	i = 0;
	token = 0;
	while (i < data->n_cmd)
	{
		while (data->full_cmd[token] != '|' && data->full_cmd[token])
			token ++;
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
	data->full_cmd = split_cmd(data->input);
	define_cmds(data);
}


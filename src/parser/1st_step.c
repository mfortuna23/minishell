/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1st_step.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfortuna <mfortuna@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 11:38:58 by mfortuna          #+#    #+#             */
/*   Updated: 2025/01/20 21:05:23 by mfortuna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/* recives input from user */
int	get_cmd(t_data *data, char **env)
{
	data_init(data, env);
	data->input = readline(get_prompt(data));
	while (input_user(data) >= 0)
	{
		if (data->check == 0)
		{
			if (data->cmd->cmd[0] && ft_strnstr(data->cmd->cmd[0], "cd\0", 3))
				ft_cd(data, data->cmd, 0);
			else
			{
				set_path(data);
				r_value(ft_execute(data, data->cmd), 1);
			}
		}
		if (data->cmd)
			delete_cmds(data);
		free(data->prompt);
		data->input = readline(get_prompt(data));
	}
	ms_bomb(data, 0);
	clear_history();
	return (0);
}

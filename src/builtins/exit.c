/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfortuna <mfortuna@student.42.pt>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 11:35:17 by mfortuna          #+#    #+#             */
/*   Updated: 2024/11/21 18:18:40 by mfortuna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void r_value(t_data *data)
{
	data->return_v = ft_atoi_base(data->cmd->cmd[1]);
	while (data->return_v < 0)
		data->return_v += 256;
	while (data->return_v >= 256)
		data->return_v = data->return_v - 256;
}

int exit_error(t_data *data, int args)
{
	if (args == 1)
		ft_fprintf(2, 1, "exit\nMS: exit: %s:"
			" numeric argument required\n", data->cmd->cmd[1]);
	if (args == 2)
		ft_fprintf(2, 1, "exit\nMS: exit: too many arguments\n");
	data->return_v = 1;
	data->check = 1;
	return (1);
}

int ft_exit(t_data *data, int i)
{
	if (data->cmd->pipe)
		return (1);
	if (!data->cmd->cmd)
		return (1);
	data->return_v = 0;
	if (ft_strncmp(data->cmd->cmd[0], "exit\0", 5) == 0)
	{
		if (data->cmd->cmd[1])
		{
			while (data->cmd->cmd[1][i])
			{
				if (ft_isdigit(data->cmd->cmd[1][i]) == 0 && data->cmd->cmd[1][i] != '-')
					return (exit_error(data, 1));
				i++;
			}
			if (data->cmd->cmd[2])
				return (exit_error(data, 2));
			r_value(data);
		}
		data->check = -1;
		ft_fprintf(2, 0, "exit\n");
		return (0);
	}
	return (1);
}

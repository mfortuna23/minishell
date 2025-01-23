/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfortuna <mfortuna@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 11:35:17 by mfortuna          #+#    #+#             */
/*   Updated: 2025/01/23 10:38:18 by mfortuna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	r_exit(t_data *data, t_cmd *cmd, int check)
{
	int	value;

	value = ft_atoi(cmd->cmd[1]);
	while (value < 0)
		value += 256;
	while (value >= 256)
		value = value - 256;
	r_value(value, 1);
	data->return_v = value;
	if (check == 1)
	{
		printf("exit\n");
		return (0);
	}
	return (value);
}

int	exit_error(t_data *data, int args)
{
	if (args == 1)
	{
		printf("exit\n");
		ft_fprintf(2, 1, "MS: exit: %s:"
			" numeric argument required\n", data->cmd->cmd[1]);
	}
	if (args == 2)
	{
		printf("exit\n");
		ft_fprintf(2, 1, "MS: exit: too many arguments\n");
		r_value(1, 1);
		data->check = 1;
		return (1);
	}
	r_value(2, 1);
	data->check = -1;
	return (0);
}

int	ft_exit(t_data *data, t_cmd *cmd, int i, int check)
{
	if (!cmd->cmd || !cmd->cmd[0] || (data->cmd->pipe && check == 1))
		return (1);
	if (ft_strncmp(cmd->cmd[0], "exit\0", 5) != 0)
		return (1);
	r_value(0, 1);
	if (cmd->cmd[1])
	{
		while (cmd->cmd[1][i])
		{
			if (ft_isdigit(cmd->cmd[1][i]) == 0 && \
			cmd->cmd[1][i] != '-' && cmd->cmd[1][i] != '+')
				return (exit_error(data, 1));
			i++;
		}
		if (cmd->cmd[2])
			return (exit_error(data, 2));
		return (r_exit(data, cmd, check));
	}
	if (!data->cmd->pipe && check == 1)
	{
		data->check = -1;
		ft_fprintf(1, 1, "exit\n");
		return (r_value(data->return_v, 1), 0);
	}
	return (r_value(data->return_v, 1));
}

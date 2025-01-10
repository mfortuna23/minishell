/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfortuna <mfortuna@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 11:35:17 by mfortuna          #+#    #+#             */
/*   Updated: 2025/01/08 16:41:14 by mfortuna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	r_exit(t_data *data)
{
	int	value;

	value = ft_atoi(data->cmd->cmd[1]);
	while (value < 0)
		value += 256;
	while (value >= 256)
		value = value - 256;
	r_value(value, 1);
}

int	exit_error(t_data *data, int args)
{
	if (args == 1)
		ft_fprintf(2, 1, "exit\nMS: exit: %s:"
			" numeric argument required\n", data->cmd->cmd[1]);
	if (args == 2)
	{
		ft_fprintf(2, 1, "exit\nMS: exit: too many arguments\n");
		r_value(2, 1);
		data->check = 1;
		return (1);
	}
	r_value(1, 1);
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
		r_exit(data);
	}
	if (!data->cmd->pipe && check == 1)
	{
		data->check = -1;
		ft_fprintf(2, 0, "exit\n");
		return (0);
	}
	return (r_value(0, 0));
}

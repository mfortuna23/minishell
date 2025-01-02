/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfortuna <mfortuna@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 19:43:59 by mfortuna          #+#    #+#             */
/*   Updated: 2025/01/02 14:04:51 by mfortuna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	unset_var(t_data *data, char *str)
{
	t_env	*node;
	t_env	*tmp;

	node = NULL;
	tmp = data->var;
	node = find_var(data, str);
	if (!node)
		return ;
	if (node == data->var)
	{
		data->var = node->next;
		free_env(node);
		return ;
	}
	while (tmp->next != node)
		tmp = tmp->next;
	tmp->next = node->next;
	free_env(node);
}

int	ft_unset(t_data	*data, t_cmd *cmd)
{
	int	i;

	i = 1;
	r_value(0, 1);
	if (built_flags(cmd->cmd, 1) == 2)
		return (r_value(2, 1));
	if (data->cmd->pipe || !cmd->cmd[i])
		return (1);
	while (cmd->cmd[i])
	{
		unset_var(data, cmd->cmd[i]);
		i++;
	}
	return (0);
}

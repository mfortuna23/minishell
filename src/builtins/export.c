/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariafortunato <mariafortunato@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 10:15:34 by mariafortun       #+#    #+#             */
/*   Updated: 2024/11/08 10:16:36 by mariafortun      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int		new_var(t_data *data, char *name)
{
	t_env	*node;

	add_last_env(&data->var);
	node = find_last_env(&data->var);
	node->name = ft_strdup(name);
	node->full = ft_strdup(data->cmd->cmd[1]);
	if ((ft_strchr(data->cmd->cmd[1], '=') + 1) == 0)
		return (0);
	node->value = ft_strdup(ft_strchr(data->cmd->cmd[1], '=') + 1);
	return (0);
}

int exist_var(t_data *data, t_env *node, char *name)
{
	t_env 	*new;
	t_env	*tmp;

	tmp = data->var;
	while(tmp->next != node)
		tmp = tmp->next;
	new = create_env_node();
	new->next = node->next;
	tmp->next = new;
	free_env(node);
	new->full = ft_strdup(data->cmd->cmd[1]);
	new->name = ft_strdup(name);
	if ((ft_strchr(data->cmd->cmd[1], '=') + 1) == 0)
		return (0);
	new->value = ft_strdup(ft_strchr(data->cmd->cmd[1], '=') + 1);
	return (0);
}

int		ft_export(t_data *data)
{
	t_env	*node;
	char	name[1024];
	int		i;

	ft_memset(name, 0, 1024);
	node = NULL;
	i = 0;
	if (data->cmd->pipe || !data->cmd->cmd[1])
		return (1);
	if (!ft_strchr(data->cmd->cmd[1], '='))
		return (1);
	while (data->cmd->cmd[1][i] != '=')
	{
		name[i] = data->cmd->cmd[1][i];
		i++;
	}
	node = find_var(data, name);
	if (!node)
		return(new_var(data, name));
	return(exist_var(data, node, name));
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfortuna <mfortuna@student.42.pt>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 02:41:38 by mfortuna          #+#    #+#             */
/*   Updated: 2024/11/15 15:56:55 by mfortuna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	new_var(t_data *data, char *name)
{
	t_env	*node;

	add_last_env(&data->var);
	node = find_last_env(&data->var);
	node->name = ft_strdup(name);
	node->full = ft_strdup(data->cmd->cmd[1]);
	if ((ft_strchr(data->cmd->cmd[1], '=') + 1) == 0)
		return (0);
	if (data->cmd->cmd[2])
		node->full = ft_strjoin(data->cmd->cmd[1], data->cmd->cmd[2]);
	else
		node->full = ft_strdup(data->cmd->cmd[1]);
	node->name = ft_strdup(name);
	if ((ft_strchr(data->cmd->cmd[1], '=') + 1) == 0)
		return (0);
	node->value = ft_substr(node->full, ft_strlen(name) + 2, \
	ft_strlen(node->full));
	node->value[ft_strlen(node->value) - 1] = 0;
	return (0);
}

int	exist_var(t_data *data, t_env *node, char *name)
{
	t_env	*new;
	t_env	*tmp;

	tmp = data->var;
	while (tmp->next != node)
		tmp = tmp->next;
	new = create_env_node();
	new->next = node->next;
	tmp->next = new;
	free_env(node);
	if (data->cmd->cmd[2])
		new->full = ft_strjoin(data->cmd->cmd[1], data->cmd->cmd[2]);
	else
		new->full = ft_strdup(data->cmd->cmd[1]);
	new->name = ft_strdup(name);
	if ((ft_strchr(data->cmd->cmd[1], '=') + 1) == 0)
		return (0);
	new->value = ft_substr(new->full, ft_strlen(name) + 2,\
	 ft_strlen(new->full));
	new->value[ft_strlen(new->value) - 1] = 0;
	return (0);
}
// not working with quotes
int	ft_export(t_data *data)
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
		return (new_var(data, name));
	return(exist_var(data, node, name));
}

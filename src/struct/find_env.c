/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfortuna <mfortuna@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 11:34:51 by mfortuna          #+#    #+#             */
/*   Updated: 2025/01/15 00:08:41 by mfortuna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_env	*find_last_env(t_env **env)
{
	t_env	*node;

	node = (*env);
	if (node == NULL)
		return (NULL);
	while (node->next != NULL)
		node = node->next;
	return (node);
}

t_env	*find_var(t_data *data, char *name)
{
	t_env	*node;

	node = data->var;
	if (!name || name[0] == 0)
		return (NULL);
	while (node)
	{
		if (ft_strncmp(node->name, name, ft_strlen(name)) == 0)
			return (node);
		node = node->next;
	}
	return (NULL);
}

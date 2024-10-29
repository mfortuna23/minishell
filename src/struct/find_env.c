/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfortuna <mfortuna@student.42.pt>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 11:34:51 by mfortuna          #+#    #+#             */
/*   Updated: 2024/10/29 12:15:39 by mfortuna         ###   ########.fr       */
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
	while (node)
	{
		if (ft_strncmp(node->name, name, ft_strlen(name)) == 0)
			return (node);
		node = node->next;
	}
	return (NULL);
}
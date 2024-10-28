/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfortuna <mfortuna@student.42.pt>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 09:19:49 by mfortuna          #+#    #+#             */
/*   Updated: 2024/10/28 11:40:49 by mfortuna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_env	*create_env_node(void)
{
	t_env	*env;

	env = NULL;
	env = malloc(sizeof(t_env));
	env->full = NULL;
	env->name = NULL;
	env->value = NULL;
	env->next = NULL;
	return (env);
}
void	add_last_env(t_env **head)
{
	t_env	*last;

	last = NULL;
	if ((*head) == NULL)
	{
		(*head) = create_env_node();
		return ;
	}
	last = (*head);
	while(last->next != NULL)
		last = last->next;
	last->next = create_env_node();
}

void	free_env(t_env *del)
{
	if (del->full)
		free(del->full);
	if (del->name)
		free(del->name);
	if (del->value)
		free(del->value);
	free(del);
}

void	del_lastenv(t_data *data)
{
	t_env	*node;
	t_env	*del;

	del = NULL;
	node = data->var;
	if (node == NULL)
		return ;
	if (node->next == NULL)
	{
		free_env(node);
		data->var = NULL;
		return ;
	}
	while (node->next != NULL)
	{
		del = node;
		node = node->next;
	}
	del->next = NULL;
	free_env(node);
}

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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfortuna <mfortuna@student.42.pt>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 09:19:49 by mfortuna          #+#    #+#             */
/*   Updated: 2024/10/30 13:47:04 by mfortuna         ###   ########.fr       */
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
	env->alive = true;
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

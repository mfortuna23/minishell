/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariafortunato <mariafortunato@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 11:35:23 by mfortuna          #+#    #+#             */
/*   Updated: 2024/11/08 09:39:59 by mariafortun      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

void	del_varenv(t_data *data, char *name)
{
	t_env	*node;
	t_env	*del;

	del = find_var(data, name);
	node = data->var;
	if (del == NULL || node == NULL)
		return ;
	if (del == data->var)
	{
		data->var = data->var->next;
		return (free_env(del));
	}
	while (node->next != del)
		node = node->next;
	if (node->next->next == NULL)
		node->next = NULL;
	else
		node->next = node->next->next;
	free_env(del);
}

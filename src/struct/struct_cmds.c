/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_cmds.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfortuna <mfortuna@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 11:31:46 by mfortuna          #+#    #+#             */
/*   Updated: 2025/01/15 00:33:08 by mfortuna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_cmd	*create_node(void)
{
	t_cmd	*node;

	node = NULL;
	node = malloc(sizeof(t_cmd));
	node->cmd = ft_calloc(256, sizeof(char *));
	node->path = NULL;
	node->in_n = 0;
	node->fd_out = 1;
	node->fd_in = 0;
	node->out_n = 0;
	node->file = NULL;
	node->pipe = false;
	node->return_value = 0;
	node->next = NULL;
	node->pid = -1;
	node->path_to_cmd = NULL;
	node->builtin = false;
	return (node);
}

void	add_last(t_cmd **head)
{
	t_cmd	*last;

	last = NULL;
	if ((*head) == NULL)
	{
		(*head) = create_node();
		return ;
	}
	last = (*head);
	while (last->next != NULL)
		last = last->next;
	last->next = create_node();
}

void	create_cmds(t_data *data)
{
	t_cmd	*head;

	head = NULL;
	add_last(&head);
	data->cmd = head;
}

void	free_mem(t_cmd *del)
{
	if (del->cmd != NULL)
		ft_freearr(del->cmd);
	if (del->file)
		files_bomb(del->file);
	if (del->path != NULL)
		free(del->path);
	if (del->path_to_cmd != NULL)
		ft_freearr(del->path_to_cmd);
	free(del);
}

void	delete_last(t_data *data)
{
	t_cmd	*last;
	t_cmd	*del;

	last = data->cmd;
	del = NULL;
	if (last->next == NULL)
	{
		free_mem(last);
		data->cmd = NULL;
		return ;
	}
	while (last->next->next != NULL)
		last = last->next;
	del = last->next;
	last->next = NULL;
	free_mem(del);
}

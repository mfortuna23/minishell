/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_cmds.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfortuna <mfortuna@student.42.pt>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 11:31:46 by mfortuna          #+#    #+#             */
/*   Updated: 2024/09/05 12:15:11 by mfortuna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_cmd	*create_node(void)
{
	t_cmd	*node;

	node = NULL;
	node = malloc(sizeof(t_cmd));
	node->cmd = NULL;
	node->path = NULL;
	node->full_cmd = NULL;
	node->args = NULL;
	node->fd_in = -1;
	node->fd_out = -1;
	node->infile = NULL;
	node->outfile = NULL;
	node->pipe = false;
	node->next = NULL;
	node->pid = NULL;
	return (node);
}

void add_last(t_cmd **head)
{
	t_cmd 	*last;

	last = NULL;
	if ((*head) == NULL)
	{
		(*head) = create_node();
		return ;
	}
	last = (*head);
	while(last->next != NULL)
		last = last->next;
	last->next = create_node();
}

t_cmd	**create_cmds(int n)
{
	t_cmd	**head;

	int 	i;
	head = NULL;
	i = 0;
	while(i < n)
	{
		add_last(head);
		i++;
	}
	return(head);
}


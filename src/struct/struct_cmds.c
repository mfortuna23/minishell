/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_cmds.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfortuna <mfortuna@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 11:31:46 by mfortuna          #+#    #+#             */
/*   Updated: 2024/12/03 11:11:54 by mfortuna         ###   ########.fr       */
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
	node->full_tokens = NULL;
	node->fd_in = 0;
	node->fd_out = 1;
	node->infile = NULL;
	node->outfile = NULL;
	node->pipe = false;
	node->here_doc = false;
	node->appen = false;
	node->return_value = 0;
	node->next = NULL;
	node->pid = -1;
	node->path_to_cmd = NULL;
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
	if (del->here_doc)
		unlink(del->infile);
	if (del->cmd != NULL)
		ft_freearr(del->cmd);
	if (del->infile != NULL)
		free (del->infile);
	if (del->outfile != NULL)
		free(del->outfile);
	if (del->full_tokens != NULL)
		free(del->full_tokens);
	if (del->path != NULL)
		free(del->path);
	if (del->path_to_cmd != NULL)
		ft_freearr(del->path_to_cmd);
	free (del);
}

void	delete_last (t_data *data)
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

void	delete_cmds(t_data *data)
{
	if (data->input)
		free(data->input);
	if (data->parser)
		free(data->parser);
	if (data->tokens)
		ft_freearr(data->tokens);
	while (data->cmd)
		delete_last(data);
	return ;
}

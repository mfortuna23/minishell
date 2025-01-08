/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_files.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfortuna <mfortuna@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 11:38:44 by mfortuna          #+#    #+#             */
/*   Updated: 2025/01/08 14:13:56 by mfortuna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_files		*node_file(t_data *data, enum e_type redir, char *name)
{
	t_files	*new;

	new = malloc(sizeof(t_files));
	new->redir = redir;
	new->hd_buffer = NULL;
	if (redir == R_HD)
		new->name = ft_strdup(name);
	else
		new->name = ft_strdup_noquotes(data, name, \
		ft_calloc(256, sizeof(char)), true);
	new->next = NULL;
	return (new);
}

void	add_last_file(t_data *data, t_files **head, \
enum e_type redir, char *name)
{
	t_files	*node;

	node = NULL;
	if (*head == NULL)
	{
		*head = node_file(data, redir, name);
		return ;
	}
	node = *head;
	while (node->next != NULL)
		node = node->next;
	node->next = node_file(data, redir, name);
}

void	free_file(t_files *del)
{
	free(del->name);
	if (del->redir == R_HD)
		free(del->hd_buffer);
	free(del);
}

void	delete_last_file(t_files **head)
{
	t_files	*last;
	t_files	*prev;

	if (head == NULL || (*head) == NULL)
		return ;
	last = *head;
	prev = *head;
	if ((*head)->next == NULL)
	{
		free_file((*head));
		(*head) = NULL;
		head = NULL;
		return ;
	}
	while (last->next != NULL)
		last = last->next;
	while (prev->next != last)
		prev = prev->next;
	free_file(last);
	prev->next = NULL;
}

void	files_bomb(t_files *head)
{
	while (head != NULL)
		delete_last_file(&head);
}

t_files	*findlast_file(t_files **head)
{
	t_files	*current;

	current = NULL;
	if (!head)
		return (NULL);
	current = (*head);
	if (!current)
		return (NULL);
	while (current)
	{
		if (current->next == NULL)
			return (current);
		current = current->next;
	}
	return (NULL);
}

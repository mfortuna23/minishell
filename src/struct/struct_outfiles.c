/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_outfiles.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfortuna <mfortuna@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 19:26:54 by mfortuna          #+#    #+#             */
/*   Updated: 2024/12/11 11:46:17 by mfortuna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_outfile	*create_outfile(void)
{
	t_outfile	*node;

	node = malloc(sizeof(t_outfile));
	node->name = NULL;
	node->appen = false;
	node->next = NULL;
	return (node);
}

void	add_last_outfile(t_data *d, t_outfile **head, bool ap, char *n)
{
	t_outfile	*file;

	file = NULL;
	if (*head == NULL)
	{
		*head = create_outfile();
		file = *head;
		if (ap == true)
			file->appen = true;
		file->name = ft_strdup_noquotes(d, n, ft_calloc(256, sizeof(char)), \
		true);
		return ;
	}
	file = (*head);
	while (file->next != NULL)
		file = file->next;
	file->next = create_outfile();
	file = file->next;
	if (ap == true)
		file->appen = true;
	file->name = ft_strdup_noquotes(d, n, ft_calloc(256, sizeof(char)), true);
}

void	delete_last_outfile(t_outfile **head)
{
	t_outfile	*last;
	t_outfile	*prev;

	if (head == NULL || *head == NULL)
		return ;
	if ((*head)->next == NULL)
	{
		free((*head)->name);
		free(*head);
		(*head) = NULL;
		head = NULL;
		return ;
	}
	last = *head;
	prev = *head;
	if (!last)
		return ;
	while (last->next != NULL)
		last = last->next;
	while (prev->next != last)
		prev = prev->next;
	prev->next = NULL;
	free(last->name);
	free(last);
}

void	outfile_bomb(t_outfile *head)
{
	while (head != NULL)
		delete_last_outfile(&head);
}

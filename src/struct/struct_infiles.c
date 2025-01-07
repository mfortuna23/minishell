/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_infiles.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfortuna <mfortuna@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 10:52:43 by mfortuna          #+#    #+#             */
/*   Updated: 2025/01/07 18:37:52 by mfortuna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_infile	*create_infile(void)
{
	t_infile	*node;

	node = malloc(sizeof(t_infile));
	node->name = NULL;
	node->hd_buffer = NULL;
	node->here_doc = false;
	node->next = NULL;
	return (node);
}


void	add_last_infile(t_data *d, t_infile **head, bool hd, char *n)
{
	t_infile	*file;

	file = NULL;
	printf("hello, im creating a new file and my name is %s\n", n);
	if (*head == NULL)
	{
		*head = create_infile();
		file = *head;
		file->here_doc = hd;
		if (hd == true)
			file->name = ft_strdup(n);
		else
			file->name = ft_strdup_noquotes(d, n, ft_calloc(256, sizeof(char)), \
			true);
		return ;
	}
	file = *head;
	while (file->next != NULL)
		file = file->next;
	file->next = create_infile();
	file = file->next;
	hd = true_false(hd);
	file->name = ft_strdup_noquotes(d, n, ft_calloc(256, sizeof(char)), hd);
}

void	free_in(t_infile *node)
{
	if (node->hd_buffer)
		free(node->hd_buffer);
	free(node->name);
	free(node);
}

void	delete_last_infile(t_infile **head)
{
	t_infile	*last;
	t_infile	*prev;

	if (head == NULL || *head == NULL)
		return ;
	if ((*head)->next == NULL)
	{
		free_in(*head);
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
	free_in(last);
}

t_infile	*findlast_in(t_infile **head)
{
	t_infile	*current;

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

void	infile_bomb(t_infile *head)
{
	while (head != NULL)
		delete_last_infile(&head);
}

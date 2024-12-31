/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_aux.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfortuna <mfortuna@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 16:56:07 by tbezerra          #+#    #+#             */
/*   Updated: 2024/12/23 12:06:13 by mfortuna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	clear_exit(t_data *data, int status)
{
	delete_cmds(data);
	del_lastenv(data);
	free(data->env);
	free(data->input);
	free(data->parser);
	exit(status);
}

void	set_path(t_data *data)
{
	t_cmd	*current;

	current = data->cmd;
	if (!current)
		exit(0);
	current->path_to_cmd = get_paths(data);
	while (current)
	{
		current->path = find_path(data, current);
		current = current->next;
	}
}

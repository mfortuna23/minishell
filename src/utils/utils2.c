/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfortuna <mfortuna@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 20:20:07 by mfortuna          #+#    #+#             */
/*   Updated: 2025/01/15 00:33:16 by mfortuna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	arr_count(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
		i++;
	return (i);
}

char	**ft_arrdup(char **old)
{
	char	**new;
	int		i;

	i = 0;
	new = ft_calloc(arr_count(old) + 1, sizeof (char *));
	while (old[i])
	{
		new[i] = ft_strdup(old[i]);
		i++;
	}
	i = 0;
	return (new);
}

void	files_bomb(t_files *head)
{
	while (head != NULL)
		delete_last_file(&head);
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

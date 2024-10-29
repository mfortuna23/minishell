/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfortuna <mfortuna@student.42.pt>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 11:22:58 by mfortuna          #+#    #+#             */
/*   Updated: 2024/10/29 12:55:16 by mfortuna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int		check_for_built(t_data *data)
{
	t_env *node;

	node = data->var;
	if (ft_strnstr(data->tokens[0], "cd", 2))
	{
		if (chdir(data->tokens[1]) < 0) // also, need to check if it is a file
			ft_fprintf(2, 1,"bash: cd: %s: Not a directory\n", data->tokens[1]);
		return (1);
	}
	else if (ft_strncmp(data->tokens[0], "unset", 5) == 0)
	{
		del_varenv(data, data->tokens[1]);
		return (1);
	}
	else if (ft_strncmp(data->tokens[0], "env", 5) == 0)
	{
		while (node)
		{
			printf("%s\n", node->full);
			node = node->next;
		}
		return (1);
	}
	else if (ft_strncmp(data->tokens[0], "pwd", 3) == 0)
		return (ft_fprintf(1, 1, "%s\n", data->path));
	return (0);
}

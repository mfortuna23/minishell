/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfortuna <mfortuna@student.42.pt>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 11:22:58 by mfortuna          #+#    #+#             */
/*   Updated: 2024/10/28 12:08:41 by mfortuna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int		check_for_built(t_data *data)
{
	if (ft_strnstr(data->tokens[0], "cd", 2))
	{
		if (chdir(data->tokens[1]) < 0) // also, need to check if it is a file
			ft_fprintf(2, 1,"bash: cd: %s: Not a directory\n", data->tokens[1]);
		return (1);
	}
	return (0);
}
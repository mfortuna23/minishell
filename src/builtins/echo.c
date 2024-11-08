/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariafortunato <mariafortunato@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 10:32:51 by mariafortun       #+#    #+#             */
/*   Updated: 2024/11/08 11:46:48 by mariafortun      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int ft_echo(t_data *data, char **cmd, int x, int y)
{
	bool	new_line;
    char	var[1024];
	t_env	*node;

	node = NULL;
	ft_memset(var, 0, 1024);
	new_line = true;
	if (ft_strncmp(cmd[x], "-n", 2) == 0)
		new_line = false;
	x++;
	while (cmd[x])
	{
		while (cmd[x][y])
		{
			// if (cmd[x][y] == '$')
			// {
			// 	node = find
			// }
			y++;
		}
		x++;
	}
	(void)data;
	(void)node;
	(void)new_line;
	return (0);
}

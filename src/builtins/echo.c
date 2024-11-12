/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfortuna <mfortuna@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 02:40:57 by mfortuna          #+#    #+#             */
/*   Updated: 2024/11/12 00:17:33 by mfortuna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int print_var(t_data *data, char *cmd, int i)
{
	t_env	*var;
	char	name[1024];

	var = NULL;
	ft_memset(name, 0, 1024);
	while ((cmd[i]) && cmd[i] != ' ' && cmd[i] != 34)
	{
		name[i] = cmd[i];
		i++;
	}
	if (cmd[i] == 34)
		i++;
	var = find_var(data, name);
	if (!var)
		return (++i);
	printf("%s", var->value);
	return(++i);
}

void print_echo(t_data *data, char *cmd, int i)
{
	char c;

	c = cmd[i];
	while (cmd[i])
	{
		if (c == 39)
		{
			while(cmd[++i] != c)
				ft_putchar_fd(cmd[i], 1);
			return ;
		}
		if (cmd[i] == 34)
			i++;
		else if (cmd[i] == '$')
			i = i + print_var(data, (cmd + i + 1), 0);
		else
			ft_putchar_fd(cmd[i++], 1);
	}
}

int ft_echo(t_data *data, char **cmd, int x)
{
	bool	new_line;
    char	var[1024];

	ft_memset(var, 0, 1024);
	new_line = true;
	if (ft_strncmp(cmd[x], "-n", 2) == 0)
	{
		new_line = false;
		x++;
	}
	while (cmd[x])
	{
		print_echo(data, cmd[x], 0);
		x++;
	}
	if (new_line)
		printf("\n");
	return (0);
}

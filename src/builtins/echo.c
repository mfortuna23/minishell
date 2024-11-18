/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfortuna <mfortuna@student.42.pt>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 02:40:57 by mfortuna          #+#    #+#             */
/*   Updated: 2024/11/15 16:00:35 by mfortuna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	print_var(t_data *data, char *cmd, int i)
{
	t_env	*var;
	char	name[1024];

	var = NULL;
	ft_memset(name, 0, 1024);
	if (cmd[i] == '?')
		return (ft_fprintf(1, 1, "%i", data->return_v));
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
	if (var->alive)
		ft_printf("%s", var->value);
	return (++i);
}

void	print_echo(t_data *data, char *cmd, int i)
{
	char	c;

	c = cmd[i];
	while (cmd[i])
	{
		if (c == 39)
		{
			while (cmd[++i] != c)
				ft_putchar_fd(cmd[i], 1);
			return ;
		}
		if (cmd[i] == 34)
			i++;
		if (cmd[i] == '$')
			i = i + print_var(data, (cmd + i + 1), 0);
		else
			ft_printf("%c", cmd[i++]);
	}
}

int	ft_echo(t_data *data, char **cmd, int x)
{
	bool	new_line;
    char	var[1024];
	char	c;

	ft_memset(var, 0, 1024);
	new_line = true;
	if (ft_strncmp(cmd[x], "-n", 2) == 0)
	{
		new_line = false;
		x++;
	}
	while (cmd[x])
	{
		c = cmd[x][0];
		print_echo(data, cmd[x], 0);
		if (c != 34 && cmd[x][0] != 0)
			ft_printf("%c", 32);
		x++;
	}
	if (new_line)
		printf("\n");
	return (0);
}

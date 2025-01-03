/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfortuna <mfortuna@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 02:40:57 by mfortuna          #+#    #+#             */
/*   Updated: 2025/01/03 00:24:46 by mfortuna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	print_var(t_data *data, char *cmd, int i, int fd_out)
{
	t_env	*var;
	char	name[1024];

	var = NULL;
	ft_memset(name, 0, 1024);
	if (cmd[i] == 0)
		return (ft_fprintf(fd_out, 1, "%c", '$'));
	if (cmd[i] == '?')
		return (ft_fprintf(fd_out, 2, "%i", r_value(0, 0)));
	while ((cmd[i]) && cmd[i] != ' ' && cmd[i] != 34)
	{
		name[i] = cmd[i];
		i++;
	}
	if (cmd[i] == 34)
		i++;
	var = find_var(data, name);
	if (!var)
		return (i);
	if (var->alive)
		ft_fprintf(fd_out, 0, "%s", var->value);
	return (++i);
}

void	print_echo(t_cmd *cmd, char *args, int x)
{
	char	c;
	int		i;

	i = 0;
	c = args[i];
	while (args[i])
	{
		if (c == 39)
		{
			while (args[++i] != c)
				ft_putchar_fd(args[i], 1);
			return ;
		}
		if (args[i] == 34)
			i++;
		// if (cmd[i] == '$')
		// 	i = print_var(data, cmd, i + 1, fd_out);
		else
			printf("%c", args[i++]);
	}
	if (x == arr_count(cmd->cmd) - 1)
		return ;
	ft_putchar_fd(' ', 1);
}

int	ft_echo(t_data *data, t_cmd *cmd, int x)
{
	int		new_line;
	char	var[1024];
	// char	c;

	ft_memset(var, 0, 1024);
	(void)data;
	new_line = 0;
	if (!cmd->cmd[x])
		return (0);
	new_line = built_flags(cmd->cmd, 0);
	if (new_line == 2)
		return (2);
	while (cmd->cmd[x])
	{
		// c = cmd->cmd[x][0];
		print_echo(cmd, cmd->cmd[x], x);
		// if ((c != 34 && cmd->cmd[x][0] != 0) || cmd->cmd[x + 1][0] != 0)
		// 	ft_printf("%c", 32);
		x++;
	}
	if (new_line == 0)
		printf("\n");
	return (0);
}

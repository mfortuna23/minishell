/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfortuna <mfortuna@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 02:40:57 by mfortuna          #+#    #+#             */
/*   Updated: 2024/11/20 22:51:57 by mfortuna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	print_var(t_data *data, char *cmd, int i, int fd_out)
{
	t_env	*var;
	char	name[1024];

	var = NULL;
	ft_memset(name, 0, 1024);
	if (cmd[i] == '?')
		return (ft_fprintf(fd_out, 2, "%i", data->return_v));
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
		ft_fprintf(fd_out, 0,"%s", var->value);
	return (++i);
}

void	print_echo(t_data *data, char *cmd, int i, int fd_out)
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
			i = i + print_var(data, (cmd + i + 1), 0, fd_out);
		else
			ft_fprintf(fd_out, 0,"%c", cmd[i++]);
	}
}

int	ft_echo(t_data *data, t_cmd *cmd, int x)
{
	bool	new_line;
    char	var[1024];
	char	c;

	ft_memset(var, 0, 1024);
	new_line = true;
	if (ft_strncmp(cmd->cmd[x], "-n", 2) == 0)
	{
		new_line = false;
		x++;
	}
	while (cmd->cmd[x])
	{
		c = cmd->cmd[x][0];
		print_echo(data, cmd->cmd[x], 0, cmd->fd_out);
		if (c != 34 && cmd->cmd[x][0] != 0)
			ft_printf("%c", 32);
		x++;
	}
	if (new_line)
		printf("\n");
	return (0);
}

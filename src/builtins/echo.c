/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfortuna <mfortuna@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 02:40:57 by mfortuna          #+#    #+#             */
/*   Updated: 2025/01/03 12:27:35 by mfortuna         ###   ########.fr       */
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
	ft_fprintf(0, 1, "%s", args);
	if (x == arr_count(cmd->cmd) - 1)
		return ;
	ft_fprintf(0, 1, " ");
}

int	ft_echo(t_data *data, t_cmd *cmd, int x)
{
	int		new_line;
	char	var[1024];

	ft_memset(var, 0, 1024);
	(void)data;
	new_line = 0;
	if (!cmd->cmd[x])
		return (0);
	new_line = built_flags(cmd->cmd, 0);
	if (new_line == 2)
		return (2);
	x = new_line + 1;
	while (cmd->cmd[x])
	{
		ft_fprintf(1, 0, "%s", cmd->cmd[x]);
		if (x == arr_count(cmd->cmd) - 1)
			break ;
		ft_fprintf(1, 0, " ");
		x++;
	}
	if (new_line == 0)
		printf("\n");
	return (0);
}

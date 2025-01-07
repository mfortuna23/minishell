/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfortuna <mfortuna@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 11:22:58 by mfortuna          #+#    #+#             */
/*   Updated: 2025/01/07 11:59:32 by mfortuna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_cd(t_data *data, t_cmd *cmd, int check)
{
	r_value(0, 1);
	if (data->cmd->pipe && check == 0)
		return (0);
	if (!cmd->cmd[1] || !cmd->cmd[1][0])
		return (ft_cd2(data));
	if (built_flags(cmd->cmd, 1) == 2)
		return (r_value(2, 1));
	if (chdir(cmd->cmd[1]) < 0)
	{
		if (access(cmd->cmd[1], X_OK) < 0)
			r_value(ft_fprintf(1, 1, "MS: cd: %s: No such file"
					" or directory\n", cmd->cmd[1]), 1);
		else
			r_value(ft_fprintf(1, 1, "MS: cd: %s"
					": Not a directory\n", cmd->cmd[1]), 1);
	}
	else
		update_var(data);
	return (1);
}

int	ft_env(t_data *data)
{
	t_env	*node;

	node = data->var;
	r_value(0, 1);
	if (built_flags(data->cmd->cmd, 1) == 2)
		return (r_value(2, 1));
	while (node)
	{
		if (node->alive)
			printf("%s\n", node->full);
		node = node->next;
	}
	return (0);
}

int	export_or_unset(t_data *data, t_cmd *cmd)
{
	int		exc;

	exc = 0;
	if (!cmd->cmd || !cmd->cmd[0])
		return (2);
	if (ft_strncmp(cmd->cmd[0], "unset\0", 6) == 0)
		return (ft_unset(data, cmd));
	else if (ft_strncmp(cmd->cmd[0], "export\0", 7) == 0)
	{
		exc = ft_export(data, cmd);
		if (exc == 3)
			return (2);
		if (exc == 1)
			r_value(1, 1);
		return (0);
	}
	return (2);
}

/* return value 0: was executed | 2: NOT builtin  */
int	check_for_built(t_data *data, t_cmd	*cmd)
{
	(void)data;
	if (!cmd->cmd | !cmd->cmd[0])
		return (2);
	if (ft_strncmp(cmd->cmd[0], "env\0", 4) == 0)
		return (0);
	else if (ft_strncmp(cmd->cmd[0], "pwd\0", 4) == 0)
		return (0);
	else if (ft_strncmp(cmd->cmd[0], "echo\0", 5) == 0)
		return (0);
	else if (ft_strncmp(cmd->cmd[0], "unset\0", 6) == 0)
		return (0);
	else if (ft_strncmp(cmd->cmd[0], "export\0", 7) == 0)
		return (0);
	else if (ft_strncmp(cmd->cmd[0], "exit\0", 5) == 0)
		return (0);
	else if (ft_strncmp(cmd->cmd[0], "cd\0", 3) == 0)
		return (0);
	return (2);
}

int	execute_built(t_data *data, t_cmd *cmd)
{
	if (!cmd->cmd | !cmd->cmd[0])
	return (0);
	if (ft_strncmp(cmd->cmd[0], "env\0", 4) == 0)
		return (ft_env(data));
	else if (ft_strncmp(cmd->cmd[0], "pwd\0", 4) == 0)
		return (pwd(data, cmd));
	else if (ft_strncmp(cmd->cmd[0], "echo\0", 5) == 0)
		return (ft_echo(data, cmd, 1));
	else if (ft_strncmp(cmd->cmd[0], "unset\0", 6) == 0)
		return (0);
	else if (ft_strncmp(cmd->cmd[0], "export\0", 7) == 0)
		return (export_no_args(data, cmd, 0, count_vars(data)));
	else if (ft_strncmp(cmd->cmd[0], "exit\0", 5) == 0)
		return (ft_exit(data, cmd, 0, 0));
	else if (ft_strncmp(cmd->cmd[0], "cd\0", 3) == 0)
		ft_cd(data, cmd, 1);
	return (0);
}

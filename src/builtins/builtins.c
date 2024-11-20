/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfortuna <mfortuna@student.42.pt>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 11:22:58 by mfortuna          #+#    #+#             */
/*   Updated: 2024/11/20 11:33:11 by mfortuna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_cd(t_data *data)
{
	data->return_v = 0;
	if (data->cmd->pipe)
		return (0);
	if (!data->tokens[1])
		return (0);
	if (chdir(data->tokens[1]) < 0)
	{
		if (access(data->tokens[1], X_OK) < 0)
			data->return_v = ft_fprintf(2, 1, "bash: cd: %s"
					": No such file or directory\n", data->tokens[1]);
		else
			data->return_v = ft_fprintf(2, 1, "bash: cd: %s"
					": Not a directory\n", data->tokens[1]);
	}
	return (1);
}

int	ft_unset(t_data	*data)
{
	t_env	*node;

	node = NULL;
	data->return_v = 0;
	if (data->cmd->pipe)
		return (1);
	if (!data->cmd->cmd[1])
		return (1);
	data->return_v = 0;
	node = find_var(data, data->cmd->cmd[1]);
	node->alive = false;
	return (0);
}

int	ft_env(t_data *data)
{
	t_env	*node;

	node = data->var;
	data->return_v = 0;
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
	if (!cmd->cmd)
		return (2);
	if (ft_strncmp(cmd->cmd[0], "unset\0", 6) == 0)
		return (ft_unset(data));
	else if (ft_strncmp(cmd->cmd[0], "export\0", 7) == 0)
		return (ft_export(data));
	return (2);
}

/* return value 0: was executed | 2: NOT builtin  */
int	check_for_built(t_data *data, t_cmd	*cmd)
{
	t_env	*node;

	node = data->var;
	(void)node;
	if (ft_strncmp(cmd->cmd[0], "env\0", 4) == 0)
		return (ft_env(data));
	else if (ft_strncmp(cmd->cmd[0], "pwd\0", 4) == 0)
		return (ft_fprintf(1, 0, "%s\n", data->path));
	else if (ft_strncmp(cmd->cmd[0], "echo\0", 5) == 0)
		return (ft_echo(data, cmd, 1));
	else if (ft_strncmp(cmd->cmd[0], "unset\0", 6) == 0)
		return (1);
	else if (ft_strncmp(cmd->cmd[0], "export\0", 7) == 0)
		return (0);
	else if (ft_strncmp(cmd->cmd[0], "exit\0", 5) == 0)
		return (0);
	return (2);
}

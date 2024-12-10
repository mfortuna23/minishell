/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfortuna <mfortuna@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 11:22:58 by mfortuna          #+#    #+#             */
/*   Updated: 2024/12/05 09:35:30 by mfortuna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_cd(t_data *data)
{
	r_value(0, 1);
	if (data->cmd->pipe)
		return (0);
	if (!data->tokens[1])
		return (0);
	if (chdir(data->tokens[1]) < 0)
	{
		if (access(data->tokens[1], X_OK) < 0)
			r_value(ft_fprintf(2, 1, "MS: cd: %s: No such file"
					" or directory\n", data->tokens[1]), 1);
		else
			r_value(ft_fprintf(2, 1, "MS: cd: %s"
					": Not a directory\n", data->tokens[1]), 1);
	}
	else
		update_var(data);
	return (1);
}

void	unset_var(t_data *data, char *str)
{
	t_env	*node;
	t_env	*tmp;

	node = NULL;
	tmp = data->var;
	node = find_var(data, str);
	if (!node)
		return ;
	if (node == data->var)
	{
		data->var = node->next;
		free_env(node);
		return ;
	}
	while (tmp->next != node)
		tmp = tmp->next;
	tmp->next = node->next;
	free_env(node);
}

int	ft_unset(t_data	*data, t_cmd *cmd)
{
	int	i;

	i = 1;
	r_value(0, 1);
	if (data->cmd->pipe || !cmd->cmd[i])
		return (1);
	while (cmd->cmd[i])
	{
		unset_var(data, cmd->cmd[i]);
		i++;
	}
	return (0);
}

int	ft_env(t_data *data)
{
	t_env	*node;

	node = data->var;
	r_value(0, 1);
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
	if (!cmd->cmd)
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
		return (export_no_args(data, cmd, 0, count_vars(data)));
	else if (ft_strncmp(cmd->cmd[0], "exit\0", 5) == 0)
		return (1);
	return (2);
}

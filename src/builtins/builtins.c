/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariafortunato <mariafortunato@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 11:22:58 by mfortuna          #+#    #+#             */
/*   Updated: 2024/11/07 00:34:27 by mariafortun      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int		ft_cd(t_data *data)
{
	data->return_v = 0;
	if (data->cmd->pipe)
		return (0);
	if (!data->tokens[1])
		return (0);
	if (chdir(data->tokens[1]) < 0)
	{
		if (access(data->tokens[1], X_OK) < 0)
			data->return_v = ft_fprintf(2, 1,"bash: cd: %s"
			": No such file or directory\n", data->tokens[1]);
		else
			data->return_v =ft_fprintf(2, 1,"bash: cd: %s"
		": Not a directory\n", data->tokens[1]);
	}
	return (1);
}

int		ft_unset(t_data	*data)
{
	t_env	*node;

	node = NULL;
	data->return_v = 0; // mesmo que nao seja executado, bash nao considera erro
	if (data->cmd->pipe)
		return (1);
	if (!data->cmd->cmd[1])
		return (1);
	data->return_v = 0;
	node = find_var(data, data->cmd->cmd[1]);
	node->alive = false;
	return (0);
}

int		ft_env(t_data *data)
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

int		ft_export (t_data *data)
{
	t_env	*node;

	node = NULL;
	if (data->cmd->pipe || !data->cmd->cmd[1])
		return (1);
	if (!ft_strchr(data->cmd->cmd[1], '='))
		return (1);
	// find if the variable already exists and make it alive
	add_last_env(&data->var);
	node = find_last_env(&data->var);
	node->full = ft_strdup(data->cmd->cmd[1]);
	node->name = ft_substr(data->cmd->cmd[1], 0, ft_strchr(data->cmd->cmd[1], '=') - data->cmd->cmd[1]);
	if ((ft_strchr(data->cmd->cmd[1], '=') + 1) == 0)
	{
		if (!data->cmd->cmd[2])
			return (1);

		node->value = data->cmd->cmd[2];
		return (0);
	}
	node->value = ft_strdup(ft_strchr(data->cmd->cmd[1], '=') + 1);
	return (0);
}
/* return value 0: was executed | 1: it is built in but it was not executed | 2: NOT builtin  */
int		check_for_built(t_data *data, t_cmd	*cmd)
{
	t_env *node;

	node = data->var;
	(void)node;
	if (ft_strnstr(cmd->cmd[0], "cd", 2))
		return (ft_cd(data));
	else if (ft_strncmp(cmd->cmd[0], "unset", 5) == 0)
		return (ft_unset(data));
	else if (ft_strncmp(cmd->cmd[0], "env", 3) == 0)
		return (ft_env(data));
	else if (ft_strncmp(cmd->cmd[0], "pwd", 3) == 0)
		return (ft_fprintf(1, 1, "%s\n", data->path));
	else if (ft_strncmp(cmd->cmd[0], "export", 6) == 0)
		return (ft_export(data));
	return (2);
}

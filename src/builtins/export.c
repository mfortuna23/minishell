/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfortuna <mfortuna@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 02:41:38 by mfortuna          #+#    #+#             */
/*   Updated: 2024/11/28 16:22:44 by mfortuna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	new_var(t_data *data, char *name)
{
	t_env	*node;

	node = NULL;
	add_last_env(&data->var);
	node = find_last_env(&data->var);
	if ((ft_strchr(data->cmd->cmd[1], '=')[1]) == 0)
		return (0);
	if (data->cmd->cmd[2])
		node->full = ft_strjoin(data->cmd->cmd[1], data->cmd->cmd[2]);
	else
		node->full = ft_strdup(data->cmd->cmd[1]);
	node->name = ft_strdup(name);
	if ((ft_strchr(node->full, '=')[1]) == 0)
		return (0);
	node->value = ft_substr(node->full, ft_strlen(name) + 1, 1024);
	node->alive = true;
	return (0);
}

int	exist_var(t_data *data, t_env *node, char *name)
{
	t_env	*new;
	t_env	*tmp;

	new = NULL;
	tmp = NULL;
	tmp = data->var;
	while (tmp->next != node)
		tmp = tmp->next;
	new = create_env_node();
	new->next = node->next;
	tmp->next = new;
	free_env(node);
	if (data->cmd->cmd[2])
		new->full = ft_strjoin(data->cmd->cmd[1], data->cmd->cmd[2]);
	else
		new->full = ft_strdup(data->cmd->cmd[1]);
	new->name = ft_strdup(name);
	if ((ft_strchr(new->full, '=')[1]) == 0)
		return (0);
	if ((ft_strchr(new->full, '=') + 1)[0] == 34)
		new->value = ft_substr(data->cmd->cmd[2], 1, \
		ft_strlen(data->cmd->cmd[2]) - 2);
	new->value = ft_substr(new->full, ft_strlen(name) + 1, 1024);
	return (0);
}

// add in vars withou equal sign, it shows when export is called not env
int	ft_export(t_data *data) // TODO accept multiple vars
{
	t_env	*node;
	char	name[1024];
	int		i;

	ft_memset(name, 0, 1024);
	node = NULL;
	i = 0;
	if (data->cmd->pipe || !data->cmd->cmd[1])
		return (3);
	if (!ft_strchr(data->cmd->cmd[1], '='))
		return (1);
	if (data->cmd->cmd[1][0] == '$')
		return (ft_fprintf(2, 1, "MS: export: `$': not a valid identifier\n"));
	while (data->cmd->cmd[1][i] != '=')
	{
		name[i] = data->cmd->cmd[1][i];
		i++;
	}
	node = find_var(data, name);
	if (!node)
		return (new_var(data, name));
	return (exist_var(data, node, name));
}

int count_vars(t_data *data)
{
	t_env	*var;
	int		count;

	count = 0;
	var = data->var;
	while (var)
	{
		count ++;
		var = var->next;
	}
	return (count);
}

int	export_print(t_cmd *cmd, t_env *var, int count)
{
	if (var->alive)
	{
		ft_fprintf(cmd->fd_out, 0, "declare -x %s=", var->name);
		if (var->value)
			ft_fprintf(cmd->fd_out, 0, "\"%s\"\n", var->value);
		else
			ft_fprintf(cmd->fd_out, 0, "\"\"\n");
	}
	count ++;
	var->w = true;
	return (count);
}

int	export_no_args(t_data *data, t_cmd *cmd, int count, int n_vars)
{
	t_env	*var;
	t_env	*cmp;

	var = data->var;
	cmp = data->var;
	if (cmd->cmd[1])
		return (1);
	while (count < n_vars)
	{
		while (cmp)
		{
			if (ft_strncmp(var->name, cmp->name, 1024) > 0 && !cmp->w)
				var = cmp;
			cmp = cmp->next;
		}
		count = export_print(cmd, var, count);
		var = data->var;
		while (var && var->w)
			var = var->next;
		cmp = data->var;
	}
	return (0);
}

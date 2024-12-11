/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfortuna <mfortuna@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 02:41:38 by mfortuna          #+#    #+#             */
/*   Updated: 2024/12/05 09:42:42 by mfortuna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	new_var(t_data *data, char *str, char *name)
{
	t_env	*node;

	node = NULL;
	add_last_env(&data->var);
	node = find_last_env(&data->var);
	node->name = ft_strdup(name);
	if ((ft_strchr(str, '=')[1]) == 0)
		return (0);
	node->full = ft_strdup(str);
	if ((ft_strchr(node->full, '=')[1]) == 0)
		return (0);
	node->value = ft_substr(node->full, ft_strlen(name) + 1, 1024);
	node->alive = true;
	return (0);
}

int	exist_var(t_data *data, t_env *node, char *str, char *name)
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
	new->full = ft_strdup(str);
	new->name = ft_strdup(name);
	if ((ft_strchr(new->full, '=')[1]) == 0)
		return (0);
	new->value = ft_substr(new->full, ft_strlen(name) + 1, 1024);
	return (0);
}

char	*export_name(char *str, char *name)
{
	int		i;

	i = 0;
	ft_memset(name, 0, 256);
	while (str[i] && str[i] != '=')
	{
		name[i] = str[i];
		i ++;
	}
	return (name);
}

void	export_var(t_data *data, char *str, bool alive)
{
	t_env	*var;
	char	name[256];

	r_value(0, 1);
	var = find_var(data, export_name(str, name));
	if (!alive)
	{
		if (var)
			return ;
		add_last_env(&data->var);
		var = find_last_env(&data->var);
		var->name = ft_strdup(export_name(str, name));
		var->full = ft_strdup(export_name(str, name));
		var->alive = alive;
	}
	else if (var)
		exist_var(data, var, str, export_name(str, name));
	else
		new_var(data, str, export_name(str, name));
}

// vars cannot start numbers!!!!!!!!
int	ft_export(t_data *data, t_cmd *cmd)
{
	int	i;

	i = 1;
	if (cmd->pipe || !cmd->cmd[1])
		return (3);
	while (cmd->cmd[i])
	{
		if (ft_strncmp(cmd->cmd[i], "$\0", 2) == 0 || \
		ft_isdigit(cmd->cmd[i][0]) == 1)
		{
			r_value(1, 1);
			return (ft_fprintf(2, 1, "MS: export: `%s': not a valid"
					" identifier\n", cmd->cmd[i]));
		}
		if (!ft_strchr(cmd->cmd[i], '='))
			export_var(data, cmd->cmd[i++], false);
		else
			export_var(data, cmd->cmd[i++], true);
	}
	return (0);
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
	ft_fprintf(cmd->fd_out, 0, "declare -x %s", var->name);
	if (var->value)
		ft_fprintf(cmd->fd_out, 0, "=\"%s\"\n", var->value);
	else if (ft_strchr(var->full, '=') != NULL)
		ft_fprintf(cmd->fd_out, 0, "=\"\"\n");
	else
		ft_fprintf(cmd->fd_out, 0, "\n");
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

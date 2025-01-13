/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfortuna <mfortuna@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 02:41:38 by mfortuna          #+#    #+#             */
/*   Updated: 2025/01/13 21:30:44 by mfortuna         ###   ########.fr       */
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
	{
		node->full = ft_strdup(name);
		node->value = ft_strdup("");
		return (0);
	}
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
		if (valid_varchars(name[i]) != 0)
		{
			r_value(1, 1);
			ft_fprintf(2, 2, "MS: export: `%s': not a valid "
				"identifier\n", str);
			return (NULL);
		}
		i ++;
	}
	return (name);
}

void	export_var(t_data *data, char *str, bool alive)
{
	t_env	*var;
	char	name[256];

	r_value(0, 1);
	export_name(str, name);
	if (name[0] == 0)
		return ;
	var = find_var(data, name);
	if (!alive)
	{
		if (var)
			return ;
		add_last_env(&data->var);
		var = find_last_env(&data->var);
		var->name = ft_strdup(name);
		var->full = ft_strdup(name);
		var->alive = alive;
	}
	else if (var)
		exist_var(data, var, str, name);
	else
		new_var(data, str, name);
}

// vars cannot start numbers!!!!!!!!
int	ft_export(t_data *data, t_cmd *cmd) //TODO varname+=value fml
{
	int	i;

	i = 1;
	if (cmd->pipe || !cmd->cmd[1])
		return (3);
	if (built_flags(cmd->cmd, 1) == 2)
		return (r_value(2, 1));
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

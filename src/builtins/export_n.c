/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_n.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfortuna <mfortuna@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 19:50:37 by mfortuna          #+#    #+#             */
/*   Updated: 2024/12/30 19:51:34 by mfortuna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	count_vars(t_data *data)
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
		return (0);
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

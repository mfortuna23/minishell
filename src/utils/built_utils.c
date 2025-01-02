/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfortuna <mfortuna@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 15:01:23 by mfortuna          #+#    #+#             */
/*   Updated: 2025/01/02 15:29:03 by mfortuna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	pwd(t_data *data, t_cmd *cmd)
{
	r_value(0, 1);
	if (built_flags(cmd->cmd, 1) == 2)
		return (r_value(2, 1));
	printf("%s\n", data->path);
	return (0);
}

//if it is called from echo echo must be 0
//if returns 1 echo has -n option
//if returns 2 wrong option
int	built_flags(char **args, int echo)
{
	int	i;

	i = 1;
	if (!args[1] || args[1][0] != '-')
		return (0);
	if (echo == 0)
	{
		while (args[1][i] == 'n')
			i++;
		if (args[1][i] == 0)
			return (1);
	}
	return (ft_fprintf(2, 2, "MS: %s: %s: invalid option\n", args[0], args[1]));
}

int	ft_cd2(t_data *data)
{
	t_env	*var;

	var = NULL;
	var = find_var(data, "HOME");
	if (!var)
	{
		r_value(1, 1);
		return (ft_fprintf(2, 1, "MS: cd: HOME not set\n"));
	}
	chdir(var->value);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfortuna <mfortuna@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 15:01:23 by mfortuna          #+#    #+#             */
/*   Updated: 2025/01/23 10:37:50 by mfortuna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	pwd(t_data *data, t_cmd *cmd)
{
	r_value(0, 1);
	if (cmd->cmd[1] && cmd->cmd[1][0] == '-')
	{
		ft_fprintf(2, 2, "MS: pwd: %s: invalid option\n", cmd->cmd[1]);
		return (r_value(2, 1));
	}
	printf("%s\n", data->path);
	return (0);
}

//if it is called from echo echo must be 0
//if returns 1 echo has -n option
//if returns -1 wrong option
int	built_flags(char **arg, int echo)
{
	int	i;
	int	j;

	j = 1;
	i = 1;
	if (!arg[1] || arg[1][0] != '-')
		return (1);
	if (echo != 0)
		return (ft_fprintf(2, -1, "MS: %s: %s: invalid option\n", \
		arg[0], arg[j]));
	while (arg[j] && arg[j][0])
	{
		if (arg[j][0] != '-')
			break ;
		while (arg[j][i] == 'n')
			i++;
		if (arg[j][i] != 0)
			return (ft_fprintf(2, -1, "MS: %s: %s: invalid option\n", \
		arg[0], arg[j]));
		i = 1;
		j++;
	}
	return (j);
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
	update_var(data);
	return (0);
}

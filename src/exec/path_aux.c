/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_aux.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfortuna <mfortuna@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 16:56:07 by tbezerra          #+#    #+#             */
/*   Updated: 2025/01/15 00:25:13 by mfortuna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	clear_exit(t_data *data, int status)
{
	delete_cmds(data);
	del_lastenv(data);
	free(data->env);
	free(data->input);
	free(data->parser);
	exit(status);
}

void	set_path(t_data *data)
{
	t_cmd	*current;

	current = data->cmd;
	if (!current)
		exit(0);
	current->path_to_cmd = get_paths(data);
	while (current)
	{
		current->path = find_path(data, current);
		current = current->next;
	}
}

void	is_exec(t_cmd *cmd)
{
	if (access(cmd->cmd[0], F_OK) == 0)
	{
		if (access(cmd->cmd[0], X_OK))
		{
			cmd->path = ft_strdup(cmd->cmd[0]);
			return ;
		}
		else
			cmd->path = NULL;
	}
}

void	no_file(t_data *data, t_cmd *cmd)
{
	ft_fprintf(2, 0, "MS: %s: No such file or directory\n", cmd->cmd[0]);
	ms_bomb(data, 0);
	exit(127);
}

void	no_pathfound(t_data *data, t_cmd *c)
{
	struct stat	path_stat;

	if (c->cmd[0])
	{
		if ((ft_strncmp(c->cmd[0], "./", 2) == 0) || c->cmd[0][0] == '/')
		{
			if (stat(c->cmd[0], &path_stat) == 0)
			{
				if (S_ISDIR(path_stat.st_mode))
					ft_fprintf(2, 0, "MS: %s: Is a directory\n", c->cmd[0]);
				else
					ft_fprintf(2, 0, "MS: %s: Permission denied\n", c->cmd[0]);
			}
			else
				no_file(data, c);
			ms_bomb(data, 0);
			exit(126);
		}
		ft_fprintf(2, 0, "MS: %s: command not found\n", c->cmd[0]);
		ms_bomb(data, 0);
		exit(127);
	}
	ms_bomb(data, 0);
	exit(0);
}

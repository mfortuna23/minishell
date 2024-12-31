/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfortuna <mfortuna@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 15:20:51 by mfortuna          #+#    #+#             */
/*   Updated: 2024/12/23 12:10:18 by mfortuna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_path(char **array)
{
	int	i;

	i = 0;
	if (!array)
		return ;
	while (array[i])
		free(array[i++]);
}

char	**get_paths(t_data *data)
{
	t_env	*path_aux;
	char	**path;

	path_aux = NULL;
	path = NULL;
	if (data->cmd->path_to_cmd)
		free_path(data->cmd->path_to_cmd);
	path_aux = find_var(data, "PATH");
	if (path_aux)
		path = ft_split(path_aux->full, ':');
	return (path);
}

char	*ft_check_command_location(t_data *data, char *command, char *path_i)
{
	char	*path_aux;
	char	*path_command;

	path_command = NULL;
	if (!command)
		return (NULL);
	if (!path_i)
		return (NULL);
	path_aux = ft_strjoin(path_i, "/");
	path_command = ft_strjoin(path_aux, command);
	free(path_aux);
	if (!path_command)
		clear_exit(data, 1);
	if (access(path_command, F_OK) == 0)
		return (path_command);
	free(path_command);
	return (NULL);
}

char	*relative_path(t_data *data, char *command)
{
	char	*path_command;
	int		i;

	i = 0;
	path_command = NULL;
	if (!data->env)
		return (NULL);
	if (!data->cmd->path_to_cmd || !data->cmd->path_to_cmd)
		return (NULL);
	else
	{
		while (data->cmd->path_to_cmd[i])
		{
			path_command = ft_check_command_location(data, command,
					data->cmd->path_to_cmd[i]);
			if (path_command != NULL)
				return (path_command);
			i++;
		}
	}
	return (path_command);
}

char	*find_path(t_data *data, t_cmd *comd)
{
	char	*path_command;

	path_command = NULL;
	if (!comd->cmd || !comd->cmd[0])
		return (NULL);
	if (check_for_built(data, comd) == 0)
	{
		path_command = ft_strdup("");
		return (path_command);
	}
	if (comd->cmd[0][0] == '/' || (ft_strncmp(comd->cmd[0], "./", 2) == 0))
		path_command = ft_strdup(comd->cmd[0]);
	else if (ft_strnstr(comd->cmd[0], ".sh", ft_strlen(comd->cmd[0]))
		&& ft_strchr(comd->cmd[0], '/'))
		path_command = ft_strdup(comd->cmd[0]);
	else
		path_command = relative_path(data, comd->cmd[0]);
	return (path_command);
}

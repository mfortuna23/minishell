/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbezerra <tbezerra@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 15:20:51 by mfortuna          #+#    #+#             */
/*   Updated: 2024/11/12 10:48:34 by tbezerra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_path(char **array)
{
	int	i;

	i = 0;
	while (array[i])
		free(array[i++]);
	free(array);
}

char	**get_paths(t_data *data)
{
	t_env	*path_aux;
	char	**path;

	if (data->cmd->path_to_cmd)
		free_path(data->cmd->path_to_cmd);
	path_aux = find_var(data, "PATH");
	if (path_aux)
		path = ft_split(path_aux->full, ':');
	//free(path_aux);
	return (path);
}

char	*ft_check_command_location(t_data *data, char *command, char *path_i)
{
	char	*path_aux;
	char	*path_command;

	path_command = NULL;
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
	else
	{
		while (data->cmd->path_to_cmd[i])
		{
			path_command = ft_check_command_location(data, command, data->cmd->path_to_cmd[i]);
			//printf("Path[%d]: %s\n", i, data->cmd->path_to_cmd[i]);
			if (path_command != NULL)
				return (path_command);
			i++;
		}
	}
	return (path_command);
}

char	*find_path(t_data *data, char *command)
{
	char	*path_command;

	path_command = NULL;
	if (!command || !*command)
		return (NULL);
	if (command[0] == '/' || (ft_strncmp(command, "./", 2) == 0))
		path_command = ft_strdup(command);
	else if (ft_strnstr(command, ".sh", ft_strlen(command))
		&& ft_strchr(command, '/'))
		path_command = ft_strdup(command);
	else
		path_command = relative_path(data, command);
	return (path_command);
}

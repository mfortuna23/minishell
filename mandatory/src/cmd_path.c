/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfortuna <mfortuna@student.42.pt>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 15:20:51 by mfortuna          #+#    #+#             */
/*   Updated: 2024/09/04 15:52:45 by mfortuna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// char	*ft_joinstr(char const *s1, char const *s2)
// {
// 	size_t	size;
// 	char	*p;

// 	size = ft_strlen(s1) + ft_strlen(s2) + 1;
// 	p = (char *)ft_calloc(sizeof(char), size);
// 	if (!p)
// 		return (0);
// 	ft_memcpy(p, s1, ft_strlen(s1));
// 	ft_strlcat(p, s2, size);
// 	return (p);
// }

char	*find_path(char *cmd, char **env)
{
	char	**paths;
	char	*half_path;
	char	*full_path;
	int		i;

	i = 0;
	while (ft_strnstr(env[i], "PATH", 4) == 0)
		i++;
	paths = ft_split(env[i] + 5, ':');
	i = 0;
	while (paths[i])
	{
		half_path = ft_strjoin(paths[i], "/" );
		full_path = ft_strjoin(half_path, cmd);
		free(half_path);
		if (access(full_path, X_OK) == 0)
			return (full_path);
		free(full_path);
		i++;
	}
	ft_freearr(paths);
	paths = NULL;
	full_path = NULL;
	return (0);
}

char	**ft_fullcmd(char *cmd)
{
	char	**arr;
	int		i;

	arr = NULL;
	i = 0;
	if (ft_strrchr(cmd, '\'') == NULL && ft_strrchr(cmd, '\"') == NULL)
		return (ft_split(cmd, ' '));
	arr = ft_calloc(3, sizeof(char *));
	if (!arr)
		return (arr);
	while (cmd[i] == ' ')
		i++;
	while (cmd[i] != ' ')
		i++;
	arr[0] = ft_substr(cmd, 0, i);
	i += 2;
	arr[1] = ft_substr(cmd, i, (ft_strlen(cmd + i)) - 1);
	return (arr);
}
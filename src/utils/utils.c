/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfortuna <mfortuna@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 11:01:03 by mfortuna          #+#    #+#             */
/*   Updated: 2025/01/02 17:08:04 by mfortuna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*str_join(char *s1, char *s2)
{
	size_t	size;
	char	*p;

	if (s1 == NULL)
		size = ft_strlen(s2) + 1;
	else
		size = ft_strlen(s1) + ft_strlen(s2) + 1;
	p = (char *)ft_calloc(sizeof(char), size);
	if (!p)
		return (0);
	ft_memcpy(p, s1, ft_strlen(s1));
	ft_strlcat(p, s2, size);
	free(s1);
	free(s2);
	return (p);
}

void	ms_bomb(t_data *data, int check)
{
	if (data->cmd)
		delete_cmds(data);
	free(data->prompt);
	free(data->path);
	ft_freearr(data->env);
	if (data->pipe_n != NULL)
	{
		free(data->pipe_n);
		data->pipe_n = NULL;
	}
	if (check == 1)
	{
		if (data->input)
			free(data->input);
	}
	while (data->var)
		del_lastenv(data);
}

//if type == 0 returns last return value
int	r_value(int value, int type)
{
	static int	r_v = 0;

	if (type == 0)
		return (r_v);
	r_v = value;
	return (r_v);
}

void	change_var(t_env *var, char *name, char *value)
{
	free(var->full);
	free(var->name);
	free(var->value);
	var->name = ft_strdup(name);
	var->value = ft_strdup(value);
	var->full = ft_strjoin(name, "=");
	var->full = str_join(var->full, ft_strdup(var->value));
}

void	update_var(t_data *data)
{
	t_env	*pwd;
	t_env	*old_pwd;

	old_pwd = find_var(data, "OLDPWD");
	pwd = find_var(data, "PWD");
	if (!old_pwd && !pwd)
		return ;
	else if (!old_pwd)
	{
		getcwd(data->path, 256);
		return (change_var(pwd, "PWD", data->path));
	}
	else if (!pwd)
		return (change_var(old_pwd, "PWD", data->path));
	change_var(old_pwd, "OLDPWD", data->path);
	getcwd(data->path, 256);
	change_var(pwd, "PWD", data->path);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfortuna <mfortuna@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 00:26:38 by mfortuna          #+#    #+#             */
/*   Updated: 2025/01/15 00:27:32 by mfortuna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	change_shlvl(t_data *data)
{
	t_env	*node;
	char	*name;
	char	*full;
	int		value;

	node = NULL;
	node = find_var(data, "SHLVL");
	if (!node)
		return ;
	name = ft_strdup("SHLVL=");
	value = ft_atoi(node->value);
	value++;
	full = str_join(name, ft_itoa(value));
	exist_var(data, node, full, "SHLVL");
	free(full);
}

void	update_env(t_data *data)
{
	t_env	*node;
	int		j;

	j = 0;
	node = data->var;
	data->env = ft_calloc(count_vars(data) + 1, sizeof(char *));
	while (node)
	{
		if (node->alive)
			data->env[j++] = ft_strdup(node->full);
		node = node->next;
	}
}

void	create_env(t_data *data, char **env)
{
	t_env	*node;
	int		i;

	i = 0;
	node = NULL;
	while (env[i])
	{
		add_last_env(&data->var);
		node = find_last_env(&data->var);
		node->full = ft_strdup(env[i]);
		node->name = ft_substr(env[i], 0, ft_strchr(env[i], '=') - env[i]);
		node->value = ft_strdup(ft_strchr(env[i], '=') + 1);
		i++;
	}
	change_shlvl(data);
}

char	*get_prompt(t_data *data)
{
	char	*user;
	t_env	*var;

	var = NULL;
	getcwd(data->path, 256);
	data->prompt = ft_strdup("\001\033[7;96m\002 Minishell \001\033[0m\002");
	var = find_var(data, "USER");
	if (!var)
		user = "undefined";
	else
		user = var->value;
	data->prompt = str_join(data->prompt, ft_strdup("\001\033[7;99m\002 @"));
	data->prompt = str_join(data->prompt, ft_strdup(user));
	data->prompt = str_join(data->prompt, \
	ft_strdup(" \001\033[0m\002\001\033[7;90m\002 ~"));
	data->prompt = str_join(data->prompt, \
	ft_substr(ft_strrchr(data->path, '/'), \
	0, ft_strlen(data->path)));
	data->prompt = str_join(data->prompt, ft_strdup(" \001\033[0m\002 > "));
	ft_freearr(data->env);
	update_env(data);
	return (data->prompt);
}

void	data_init(t_data *data, char **env)
{
	data->input = NULL;
	data->parser = NULL;
	data->tokens = NULL;
	data->path = NULL;
	data->path = ft_calloc(256, sizeof(char));
	data->cmd = NULL;
	data->n_tokens = 0;
	data->var = NULL;
	data->env = NULL;
	data->i = 0;
	data->check = 0;
	data->n_cmd = 1;
	data->return_v = 0;
	data->pipe_n = NULL;
	r_value(0, 1);
	create_env(data, env);
	update_env(data);
}

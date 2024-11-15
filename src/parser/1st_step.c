/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1st_step.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfortuna <mfortuna@student.42.pt>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 11:38:58 by mfortuna          #+#    #+#             */
/*   Updated: 2024/11/15 16:12:14 by mfortuna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	create_env(t_data *data)
{
	t_env	*node;
	int		i;

	i = 0;
	node = NULL;
	while (data->env[i])
	{
		add_last_env(&data->var);
		node = find_last_env(&data->var);
		node->full = ft_strdup(data->env[i]);
		node->name = ft_substr(data->env[i], 0, \
		ft_strchr(data->env[i], '=') - data->env[i]);
		node->value = ft_strdup(ft_strchr(data->env[i], '=') + 1);
		i++;
	}
}

char	*get_prompt(t_data *data)
{
	char	*user;

	getcwd(data->path, 256);
	data->prompt = ft_strdup("\001\033[7;96m\002 MS \001\033[0m\002");
	user = getenv("USER");
	data->prompt = str_join(data->prompt, ft_strdup("\001\033[7;99m\002 @"));
	data->prompt = str_join(data->prompt, ft_strdup(user));
	data->prompt = str_join(data->prompt, \
	ft_strdup(" \001\033[0m\002\001\033[7;90m\002 ~"));
	data->prompt = str_join(data->prompt, ft_substr(ft_strrchr(data->path, '/'),\
	 0, ft_strlen(data->path)));
	data->prompt = str_join(data->prompt, ft_strdup(" \001\033[0m\002\n> "));
	return (data->prompt);
}

void	data_init(t_data *data)
{
	data->input = NULL;
	data->parser = NULL;
	data->tokens = NULL;
	data->path = NULL;
	data->path = ft_calloc(256, sizeof(char));
	data->cmd = NULL;
	data->n_tokens = 0;
	data->return_v = 0;
	data->var = NULL;
	data->i = 0;
	data->n_cmd = 1;
	create_env(data);
}
/* recives input from user */
int		get_cmd(t_data *data)
{
	data_init(data);
	data->input = readline(get_prompt(data));
	while (ft_strncmp(data->input, "exit", 4) != 0)
	{
 		if (input_user(data) == 0)
		{
			// if (data->cmd->here_doc)
			// 	here_doc(data->cmd);
			if (ft_strnstr(data->cmd->cmd[0], "cd\0", 3))
				ft_cd(data);
			else
			{
				set_path(data);
				data->return_v = ft_execute(data);
			}
		}
		if (data->cmd)
			delete_cmds(data);
		free(data->prompt);
		data->input = readline(get_prompt(data));
	}
	ms_bomb(data, 1);
	clear_history();
	return (0);
}

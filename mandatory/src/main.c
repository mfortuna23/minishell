/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfortuna <mfortuna@student.42.pt>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 11:36:53 by mfortuna          #+#    #+#             */
/*   Updated: 2024/10/25 12:09:47 by mfortuna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_prompt(t_data *data)
{
	char *user;

	getcwd(data->path, 256);
	data->prompt = ft_strdup("\001\033[7;96m\002 MS \001\033[0m\002");
	user = getenv("USER");
	data->prompt = str_join(data->prompt, ft_strdup("\001\033[7;99m\002 @"));
	data->prompt = str_join(data->prompt, ft_strdup(user));
	data->prompt = str_join(data->prompt, ft_strdup(" \001\033[0m\002\001\033[7;90m\002 ~"));
	data->prompt = str_join(data->prompt, ft_substr(ft_strrchr(data->path, '/'),\
	 0, ft_strlen(data->path)));
	data->prompt = str_join(data->prompt, ft_strdup(" \001\033[0m\002\n> "));
	return (data->prompt);
}

/* executes program */
// void	ft_execute(t_data *data)
// {
// 	pid_t	pid;

// 	pid = fork();
// 	if (pid < 0)
// 		return (perror("fork"));
// 	if (pid == 0)
// 	{
// 		execve(data->path, data->tokens, data->env);
// 		exit(0);
// 	}
// 	waitpid(pid, 0, 0);
// 	free(data->path);
// 	ft_freearr(data->tokens);
// }

t_env	*find_last_env(t_env **env)
{
	t_env	*node;

	node = (*env);
	if (node == NULL)
		return (NULL);
	while (node->next != NULL)
		node = node->next;
	return (node);
}

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
		node->name = ft_substr(data->env[i], 0, ft_strchr(data->env[i], '=') - data->env[i]);
		node->value = ft_strdup(ft_strchr(data->env[i], '=') + 1);
		i++;
	}
	printf("full: %s\n", data->var->full);
}

void data_init(t_data *data)
{
	data->input = NULL;
	data->parser = NULL;
	data->tokens = NULL;
	data->path = NULL;
	data->path = ft_calloc(256, sizeof(char));
	data->cmd = NULL;
	data->var = NULL;
	create_env(data);
}

/* recives input from user */
int	get_cmd(t_data *data)
{
	data_init(data);
	printf("full: %s\n", data->var->full);
	data->input = readline(get_prompt(data));
	while (ft_strncmp(data->input, "exit", 4) != 0)
	{
		add_history(data->input);
 		if (input_user(data) == 0)
		{
			if (ft_strnstr(data->tokens[0], "cd", 2))
			{
				if (chdir(data->tokens[1]) < 0) // also, need to check if it is a file
					ft_fprintf(2, 1,"bash: cd: %s: Not a directory\n", data->tokens[1]);
			}
			// data->path = find_path(data->tokens[0], data->env);
			// if (data->path)
			// 	ft_execute(data);
		}
		if (data->cmd)
			delete_cmds(data);
		free(data->prompt);
		data->input = readline(get_prompt(data));
	}
	ms_bomb(data);
	return (0);
}

void	ms_bomb(t_data *data)
{
	printf("full: %s\n", data->var->full);
	free(data->prompt);
	free(data->path);
	if (data->input)
		free(data->input);
	while (data->var)
		del_lastenv(data);
}

int	main(int argc, char **argv, char **env)
{
	t_data	data;

	data.env = env;
	get_cmd(&data);
	(void)argc;
	(void)argv;
	return (0);
}
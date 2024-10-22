/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfortuna <mfortuna@student.42.pt>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 11:36:53 by mfortuna          #+#    #+#             */
/*   Updated: 2024/10/22 17:12:32 by mfortuna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_prompt(t_data *data)
{
	(void)data;
	return ("\001\033[1;96m\002minishell\001\033[0m\002 \001\033[3;95m\002> \001\033[0m\002");
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

void data_init(t_data *data)
{
	data->input = NULL;
	data->parser = NULL;
	data->tokens = NULL;
	data->path = NULL;
	data->path = ft_calloc(256, sizeof(char));
	data->cmd = NULL;
}

/* recives input from user */
int	get_cmd(t_data *data)
{
	data_init(data);
	data->input = readline(get_prompt(data));
	while (ft_strncmp(data->input, "exit", 4) != 0)
	{
		add_history(data->input);
 		if (input_user(data) == 0)
		{
			if (ft_strnstr(data->tokens[0], "cd", 2))
			{
				if (chdir(data->tokens[1]) < 0)
					ft_fprintf(2, 1,"bash: cd: %s: Not a directory\n", data->tokens[1]);
			}
			printf("%s\n",getcwd(data->path, 256));
			// data->path = find_path(data->tokens[0], data->env);
			// if (data->path)
			// 	ft_execute(data);
		}
		delete_cmds(data);
		data->input = readline(get_prompt(data));
	}
	free(data->input);
	return (0);
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
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfortuna <mfortuna@student.42.pt>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 11:36:53 by mfortuna          #+#    #+#             */
/*   Updated: 2024/09/04 17:53:32 by mfortuna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	get_prompt(t_data *data)
{
	data->prompt = "\001\033[1;96m\002minishell\001\033[0m\002 \001\033[3;95m\002> \001\033[0m\002";
}

void ft_execute(t_data *data)
{
	pid_t 	pid;

	pid = fork();
	if (pid < 0)
		return(perror("fork"));
	if (pid == 0)
	{
		execve(data->path, data->full_cmd, data->env);
		exit(0);
	}
	waitpid(pid, 0, 0);
	free(data->path);
	ft_freearr(data->full_cmd);
}

int	get_cmd(t_data *data)
{
	get_prompt(data);
	data->cmd = readline(data->prompt);
	while (ft_strncmp(data->cmd, "exit", 4) != 0)
	{
		data->full_cmd = ft_fullcmd(data->cmd);
		data->path = find_path(data->full_cmd[0], data->env);
		if(data->path)
			ft_execute(data);
		free(data->cmd);
		data->cmd = readline(data->prompt);
	}
	free(data->cmd);
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
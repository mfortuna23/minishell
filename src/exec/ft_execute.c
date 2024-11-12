/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfortuna <mfortuna@student.42.pt>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 11:34:48 by mfortuna          #+#    #+#             */
/*   Updated: 2024/10/28 12:06:45 by mfortuna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int		ft_execute(t_data *data)
{
	(void)data;
	return (0);
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
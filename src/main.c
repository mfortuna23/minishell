/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfortuna <mfortuna@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 11:36:53 by mfortuna          #+#    #+#             */
/*   Updated: 2024/11/20 21:44:54 by mfortuna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"


void	sigint_handler(int signal)
{
	(void)signal;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

int	main(int argc, char **argv, char **env)
{
	t_data				data;
	struct sigaction 	sa;

    sa.sa_handler = sigint_handler;
    sa.sa_flags = SA_RESTART; // Restart system calls if interrupted
    sigaction(SIGINT, &sa, NULL);
	data.env = env;
	signal(SIGINT, &sigint_handler);
	signal(SIGQUIT, SIG_IGN);
	get_cmd(&data);
	(void)argc;
	(void)argv;
	return (data.return_v);
}

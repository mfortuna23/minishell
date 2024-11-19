/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfortuna <mfortuna@student.42.pt>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 11:36:53 by mfortuna          #+#    #+#             */
/*   Updated: 2024/11/18 11:43:44 by mfortuna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"


void	sig_handle(int signal)
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
	struct sigaction	sa;

	sa.sa_handler = sig_handle;
	sa.sa_flags = SA_RESTART;
	data.env = env;
	signal(SIGINT, &sig_handle);
	signal(SIGQUIT, SIG_IGN);
	get_cmd(&data);
	(void)argc;
	(void)argv;
	return (data.return_v);
}

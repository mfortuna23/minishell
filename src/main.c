/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfortuna <mfortuna@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 11:36:53 by mfortuna          #+#    #+#             */
/*   Updated: 2025/01/21 11:46:51 by mfortuna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	sigint_handler(int signal)
{
	if (signal == SIGINT)
	{
		rl_replace_line("", 0);
		printf("\n");
		rl_on_new_line();
		rl_redisplay();
		r_value(130, 1);
	}
}

void	set_up_sigaction(void)
{
	struct sigaction	sa;

	(void)sa;
	sigemptyset(&sa.sa_mask);
	sa.sa_handler = sigint_handler;
	sa.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sa, NULL);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTERM, SIG_IGN);
}

int	main(int argc, char **argv, char **env)
{
	t_data				data;

	if (argc > 1)
		return (ft_fprintf(2, 0, "invalid number of arguments\n"));
	set_up_sigaction();
	get_cmd(&data, env);
	(void)argc;
	(void)argv;
	return (r_value(0, 0));
}

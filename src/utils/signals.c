/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfortuna <mfortuna@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 00:30:31 by mfortuna          #+#    #+#             */
/*   Updated: 2025/01/15 00:33:26 by mfortuna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	sigchild_handler(int signal)
{
	if (signal == SIGINT)
		r_value(130, 1);
}

void	sigaction_child(void)
{
	struct sigaction	sa;

	(void)sa;
	sigemptyset(&sa.sa_mask);
	sa.sa_handler = sigchild_handler;
	sa.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sa, NULL);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTERM, SIG_IGN);
}

void	child_sig(int sig)
{
	if (sig == SIGINT)
	{
		printf("\n");
		exit(130);
	}
}

void	sig_inchild(void)
{
	struct sigaction	sa;

	(void)sa;
	sigemptyset(&sa.sa_mask);
	sa.sa_handler = child_sig;
	sa.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sa, NULL);
	signal(SIGQUIT, SIG_DFL);
	signal(SIGTERM, SIG_DFL);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfortuna <mfortuna@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 20:20:07 by mfortuna          #+#    #+#             */
/*   Updated: 2025/01/13 11:56:57 by mfortuna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	arr_count(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
		i++;
	return (i);
}

char	**ft_arrdup(char **old)
{
	char	**new;
	int		i;

	i = 0;
	new = ft_calloc(arr_count(old) + 1, sizeof (char *));
	while (old[i])
	{
		new[i] = ft_strdup(old[i]);
		i++;
	}
	i = 0;
	return (new);
}

void	sig_reset(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

void	sigchild_handler(int signal)
{
	if (signal == SIGINT)
	{
		printf("\n");
		r_value(130, 1);
	}
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
		signal(SIGINT, SIG_DFL);
		printf("\n");
		r_value(130, 1);
	}
}

void sig_inchild(void)
{
	// struct sigaction	sa;

	// (void)sa;
	// sigemptyset(&sa.sa_mask);
	// sa.sa_handler = child_sig;
	// sa.sa_flags = SA_RESTART;
	// sigaction(SIGINT, &sa, NULL);
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	signal(SIGTERM, SIG_DFL);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfortuna <mfortuna@student.42.pt>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 14:26:10 by mfortuna          #+#    #+#             */
/*   Updated: 2024/11/20 14:29:58 by mfortuna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void sig_hd(int sig)
{
	if (sig == SIGINT)
	{
		
	}
	return ;
}

void sig_reset(int sig)
{
	signal(SIGINT, SIG_DFT);
	signal(SIGQUIT, SIG_DFT);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfortuna <mfortuna@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 20:20:07 by mfortuna          #+#    #+#             */
/*   Updated: 2024/12/30 20:20:46 by mfortuna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int arr_count(char **arr)
{
	int i;

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

void sig_reset()
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

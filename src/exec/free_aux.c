/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_aux.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfortuna <mfortuna@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 16:37:43 by tbezerra          #+#    #+#             */
/*   Updated: 2024/12/30 19:55:49 by mfortuna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_no_file_err(char *fname)
{
	ft_printf("bash: %s: No such file or directory\n",
		fname);
	return ;
}

void	ft_fork_exit(t_data *data)
{
	if (data != NULL)
		printf("Data error\n");
	ms_bomb(data, 1);
}

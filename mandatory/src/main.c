/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfortuna <mfortuna@student.42.pt>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 11:36:53 by mfortuna          #+#    #+#             */
/*   Updated: 2024/09/03 11:41:31 by mfortuna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int main(int argc, char **argv, char **env)
{
	if (argc == 1)
		ft_printf("just cheking libft");
	(void)argv;
	(void)env;
	return (0);
}
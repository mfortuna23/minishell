/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfortuna <mfortuna@student.42.pt>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 11:36:53 by mfortuna          #+#    #+#             */
/*   Updated: 2024/09/03 14:14:37 by mfortuna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	get_prompt(void)
{
	char *prompt;

	prompt = NULL;
	prompt = readline("minishel ");
	while (ft_strncmp(prompt, "exit", 4) != 0)
	{
		free(prompt);
		prompt = readline("minishel ");
	}
	free(prompt);
	return (0);
}

int main(int argc, char **argv, char **env)
{
	get_prompt();
	(void)argc;
	(void)argv;
	(void)env;
	return (0);
}
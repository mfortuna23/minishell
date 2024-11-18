/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfortuna <mfortuna@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 13:24:59 by mfortuna          #+#    #+#             */
/*   Updated: 2024/11/16 11:11:51 by mfortuna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	here_doc(t_cmd *cmd)
{
	char	*input;

	input = NULL;
	input = readline("heredoc> ");
	while (ft_strncmp(input, cmd->infile, ft_strlen(cmd->infile) + 1))
	{
		ft_fprintf(cmd->fd_out, 0, "%s\n", input);
		free(input);
		input = readline("heredoc> ");
	}
	free(input);
}

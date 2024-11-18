/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfortuna <mfortuna@student.42.pt>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 13:24:59 by mfortuna          #+#    #+#             */
/*   Updated: 2024/11/18 10:58:24 by mfortuna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	here_doc(t_cmd *cmd)
{
	char	*input;
	// bool	exp;

	
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

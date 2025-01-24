/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfortuna <mfortuna@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 13:24:59 by mfortuna          #+#    #+#             */
/*   Updated: 2025/01/24 08:28:00 by mfortuna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	event(void)
{
	return (0);
}

void	write_var_hd(t_data *data, char *input, char *new, t_iter *x)
{
	char	*name;
	t_env	*var;

	name = NULL;
	var = NULL;
	x->j++;
	name = get_var_name(input + x->j);
	var = find_var(data, name);
	if (!var || !var->value || !var->value[0])
	{
		x->j += ft_strlen(name);
		free(name);
		return ;
	}
	while (var->value[x->y])
		new[x->i++] = var->value[x->y++];
	x->j += ft_strlen(name);
	free(name);
}

char	*write_hd(t_data *data, bool exp, char *input)
{
	char	*new;
	t_iter	*x;

	if (exp == false)
		return (ft_strdup(input));
	new = ft_calloc(1024, sizeof(char));
	x = init_iter();
	while (input[x->j])
	{
		if (input[x->j] == '$' && exp == true)
			write_var_hd(data, input, new, x);
		else
			new[x->i++] = input[x->j++];
	}
	free(x);
	return (new);
}

int	get_heredoc(t_data *data, t_files *infile, char *name, bool exp)
{
	char	*input;
	char	*buffer_hd;

	buffer_hd = ft_calloc(1, sizeof(char));
	set_heredoc_signals();
	while (1)
	{
		rl_event_hook = event;
		input = readline("heredoc> ");
		if (ft_heredoc_sig(-1) == 1)
			return (hd_errors(data, buffer_hd, 2));
		if (!input)
			return (hd_errors(data, buffer_hd, 1));
		if (ft_strncmp(input, name, ft_strlen(name) + 1) == 0)
			break ;
		buffer_hd = str_join(buffer_hd, write_hd(data, exp, input));
		buffer_hd = str_join(buffer_hd, ft_strdup("\n"));
	}
	if (input)
		free(input);
	infile->hd_buffer = ft_strdup(buffer_hd);
	free(buffer_hd);
	set_up_sigaction();
	return (0);
}

int	here_doc(t_data *data, t_files *node, bool exp, int y)
{
	char	*here_doc;

	(void)y;
	if (node->name[0] == 34 || node->name[0] == 39)
	{
		exp = false;
		here_doc = ft_substr(node->name, 1, ft_strlen(node->name) - 2);
	}
	else
		here_doc = ft_substr(node->name, 0, ft_strlen(node->name));
	data->check = get_heredoc(data, node, here_doc, exp);
	ft_heredoc_sig(-2);
	free(here_doc);
	return (2);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfortuna <mfortuna@student.42.pt>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 13:24:59 by mfortuna          #+#    #+#             */
/*   Updated: 2024/11/20 14:25:44 by mfortuna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	create_file(t_cmd *cmd, char *buffer)
{
	int		i;
	int		j;
	char	name[256];

	i = 0;
	j = 0;
	ft_memset(name, 0, 256);
	name[j++] = '.';
	while (cmd->infile[i])
	{
		if (cmd->infile[i] == 34)
			i++;
		name[j++] = cmd->infile[i++];
	}
	free(cmd->infile);
	cmd->infile = ft_strdup(name);
	cmd->fd_in = open(cmd->infile, O_CREAT | O_RDWR | O_TRUNC, 0666);
	ft_fprintf(cmd->fd_in, 0, "%s", buffer);
	printf("%s", buffer);
	close(cmd->fd_in);
}

int	hd_errors(char *buffer_hd, int error)
{
	if (buffer_hd)
		free (buffer_hd);
	if (error == 1) // ^D
		return (ft_fprintf(2, 1,"MS: warning: here-document"
			" at line 1 delimited by end-of-file (wanted `here')\n"));
	if (error == 2) // ^C
		return (error);
	return (3);
}

char	*w_var_buffer(t_data *data, char *input, char *buffer_hd)
{
	t_env	*var;
	char	name[256];
	char	*tmp;
	int		j;

	ft_memset(name, 0, 256);
	data->i++;
	tmp = NULL;
	j = 0;
	while ((input[data->i]) && input[data->i] != ' ')
		name[j++] = input[data->i++];
	var = find_var(data, name);
	if (!var)
		return (ft_strdup(""));
	data->i = data->i + (ft_strlen(name) - 1);
	tmp = str_join(buffer_hd, ft_strdup(var->value));
	return (tmp);
}

char	*w_buffer_hd(t_data *data, char *input, char *buffer_hd, bool exp)
{
	char *tmp;

	tmp = NULL;
	while (input[data->i])
	{
		if (exp && input[data->i] == '$')
			buffer_hd = w_var_buffer(data, input, buffer_hd);
		else
			buffer_hd = str_join(buffer_hd, ft_substr(input, data->i, 1));
		if (data->i > ft_strlen(input))
			break ;
		data->i++;
	}
	tmp = str_join(buffer_hd, ft_strdup("\n"));
	return (tmp);
}

int	get_heredoc(t_data *data, t_cmd *cmd, char *name, bool exp)
{
	char	*input;
	char	*buffer_hd;

	buffer_hd = NULL;
	buffer_hd = ft_calloc(1, sizeof(char));
	while (1)
	{
		input = readline("heredoc> ");
		if (!input)
			return (hd_errors(buffer_hd, 1));
		if (ft_strncmp(input, name, ft_strlen(name) + 1) == 0)
			break ;
		data->i = 0;
		buffer_hd = w_buffer_hd(data, input, buffer_hd, exp);
	}
	free(input);
	create_file(cmd, buffer_hd);
	free(buffer_hd);
	return (0);
}

int	here_doc(t_data *data, t_cmd *cmd, bool exp, int y)
{
	char	*here_doc;

	cmd->here_doc = true;
	if (!data->tokens[y])
		return (-9857);
	if (cmd->infile[0] == 34 || cmd->infile[0] == 39)
	{
		exp = false;
		here_doc = ft_substr(cmd->infile, 1, ft_strlen(cmd->infile) - 2);
	}
	else
		here_doc = ft_substr(cmd->infile, 0, ft_strlen(cmd->infile));
	data->check = get_heredoc(data, cmd, here_doc, exp);
	free(here_doc);
	return (2);
}

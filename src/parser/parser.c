/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfortuna <mfortuna@student.42.pt>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 11:27:08 by mfortuna          #+#    #+#             */
/*   Updated: 2024/11/19 12:09:36 by mfortuna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	print_cmds(t_data *data);

int	parsing(t_data *data, int y, int x)
{
	t_cmd	*node;

	node = data->cmd;
	while (data->tokens[y] != NULL)
	{
		if (data->tokens[y][x] == '<' || data->tokens[y][x] == '>')
			y += ft_redirect(data, node, y, 0);
		else if (data->tokens[y][x] == '|')
		{
			if (y == 0 || data->tokens[y][1] == '|')
				return (ft_fprintf(2, 1, "parser error near '|' \n"));
			add_last(&data->cmd);
			node->pipe = true;
			node = node->next;
			y++;
			data->n_cmd++;
		}
		else
			y = ft_cmd_args(data, node, y, 0);
		if (y < 0)
		{
			data->check = 1;
			return (1);
		}
	}
	if (!node->cmd)
		data->check = 1;
	return (0);
}

int	token_error(t_data *data, char *arr)
{
	data->parser = ft_calloc(1024, sizeof(char));
	less_space(data, arr, 0, 0);
	data->n_tokens = token_count(data->parser, 0, 0, 0);
	data->tokens = ft_calloc((data->n_tokens + 1), sizeof(char*));
	split_tokens(data, 0, 0, 0);
	if (check_not_req(data) == 1)
	{
		free(data->parser);
		ft_freearr(data->tokens);
		return (1);
	}
	return (0);
}

int	sep_char(char *arr, t_data *data, int j)
{
	char	c;

	c = data->input[data->i];
	arr[j++] = ' ';
	arr[j++] = data->input[data->i++];
	while (c == data->input[data->i])
		arr[j++] = data->input[data->i++];
	arr[j++] = ' ';
	return (j);
}

/* parser */
int	ft_strtok(t_data *data, int j, char c)
{
	char	arr[1024];

	ft_memset(arr, 0, 1024);
	if (!data->input)
		return (-1);
	data->i = 0;
	while (data->input[data->i])
	{
		c = data->input[data->i];
		if (c == 34 || c == 39)
		{
			arr[j++] = ' ';
			arr[j++] = data->input[data->i++];
			while ((data->input[data->i]) && (data->input[data->i] != c))
				arr[j++] = data->input[data->i++];
			arr[j++] = data->input[data->i++];
			arr[j++] = ' ';
		}
		else if (check_chars(c) > 0)
			j = sep_char(arr, data, j);
		else if (data->input[data->i])
			arr[j++] = data->input[data->i++];
	}
	return (token_error(data, arr));
}

/* recives and manages input from user */
int	input_user(t_data *data)
{
	data->check = 0;
	if (!data->input)
		return (-1);
	if (get_fullinput(data) == 1)
		return (1);
	add_history(data->input);
	if (ft_strtok(data, 0, 'a') == 1)
		return (1);
	create_cmds(data);
	if (parsing(data, 0, 0) == 1)
		return (1);
	if (data->cmd->cmd == NULL && !data->cmd->here_doc)
		return (1);
	if (ft_exit(data, 0) == 0)
		return (-1);
	if (export_or_unset(data, data->cmd) == 0)
		data->check = 1;
	//print_cmds(data);
	return (0);
}
/* 
void print_cmds(t_data *data)
{
	t_cmd	*current;
	int		i;
	int		count;

	i = 0;
	count = 1;
	current = data->cmd;
	printf("\001\033[1;93m\002the input was:\001\033[0m\002\t%s\n", data->input);
	printf("\001\033[1;93m\002after parser:\001\033[0m\002\t%s\n", data->parser);
	while (current)
	{
		printf("\n\001\033[1;93m\002command n \001\033[0m\002%d\n", count);
		while (current->cmd[i])
			printf("%s\n", current->cmd[i++]);
		printf("\001\033[1;93m\002infile is:\001\033[0m\002\t%s\n", current->infile);
		printf("\001\033[1;93m\002outfile is:\001\033[0m\002\t%s\n", current->outfile);
		printf("\001\033[1;93m\002pipe?\001\033[0m\002\t\t%s\n", \
		current->pipe ? "true" : "false");
		printf("\001\033[1;93m\002here_doc?\001\033[0m\002\t%s\n", \
		current->here_doc ? "true" : "false");
		printf("\001\033[1;93m\002appen?\001\033[0m\002\t\t%s\n", \
		current->appen ? "true" : "false");
		count++;
		i = 0;
		current = current->next;
	}
} */

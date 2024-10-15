/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfortuna <mfortuna@student.42.pt>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 11:27:08 by mfortuna          #+#    #+#             */
/*   Updated: 2024/10/15 11:20:28 by mfortuna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void print_cmds(t_data *data);
int	ft_redirect(t_data *data, t_cmd *current, int y, int x)
{
	if (data->tokens[y][x] == '<')
	{
		while (data->tokens[y][x] == '<')
			x++;
		if (x > 3)
		{
			ft_putstr_fd("parser error near : '<'", 2);
			return(-1);
		}
		else if (x > 1)
			current->here_doc = true;
		current->infile = ft_strdup(data->tokens[++y]);
		return (2);
	}
	while (data->tokens[y][x] == '>')
		x++;
	if (x > 2)
	{
		ft_putstr_fd("parser error near : '>'", 2);
		return(-1);
	}
	else if (x > 1)
		current->appen = true;
	current->outfile = ft_strdup(data->tokens[++y]);
	return (2);
}
int ft_cmd_args(t_data *data, t_cmd *node, int y, int x)
{
	int count;
	int	i;

	i = y;
	while ((data->tokens[i]) && (check_chars(data->tokens[i][x]) == 0))
		i++;
	count = i - y;
	node->cmd = malloc((count + 1) * sizeof(char *));
	i = 0;
	while ((data->tokens[y]) && check_chars(data->tokens[y][x]) == 0)
		node->cmd[i++] = ft_strdup(data->tokens[y++]);
	node->cmd[i] = 0;
	return (y);
}
int parsing(t_data *data, int y, int x)
{
	t_cmd *node;
	node = data->cmd;
	while (data->tokens[y])
	{
		if (data->tokens[y][x] == '<' || data->tokens[y][x] == '>')
			y = ft_redirect(data, node, y, 0);
			// check for multiple files
		else if (data->tokens[y][x] == '|')
		{
			if (y == 0)
				return (ft_fprintf(2, 1,"parser error near '|' \n"));
			add_last(&data->cmd);
			node->pipe = true;
			node = node->next;
			y++;
		}
		else
			y = ft_cmd_args(data, node, y, 0);
		if (y < 0)
			return (1);
	}
	return (0);
}

/* parser */
int	ft_strtok(t_data *data)
{
	char 	arr[1024];
	int		i;
	int		j;

	j = 0;
	i = 0;
	ft_memset(arr, 0, 1024);
	while (data->input[i])
	{
		while (data->input[i] <= ' ' && (data->input[i]))
			i++;
		while (check_chars(data->input[i]) == 1)
			arr[j++] = data->input[i++];
		arr[j++] = ' ';
		while (data->input[i] > ' ' && check_chars(data->input[i]) == 0)
			arr[j++] = data->input[i++];
		arr[j++] = ' ';
	}
	arr[j++] = 0;
	skip_spaces(data, arr, 0, 0);
	data->tokens = ft_split(data->parser, ' ');
	create_cmds(data);
	if (parsing(data, 0, 0) > 0)
		return (1);
	return (0);
}

/* recives and manages input from user */
int	input_user(t_data *data)
{
	if (data->input[0] == 0)
		return (1);
	if (ft_strtok(data) > 0)
		return (1);
	print_cmds(data);
	return (0);
// dealing with parser errors -> and return;
// create a function that dividies input into diferent commands
}

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
		printf("\001\033[1;93m\002pipe?\001\033[0m\002\t\t%s\n", current->pipe ? "true" : "false");
		printf("\001\033[1;93m\002here_doc?\001\033[0m\002\t%s\n", current->here_doc ? "true" : "false");
		printf("\001\033[1;93m\002appen?\001\033[0m\002\t\t%s\n", current->appen ? "true" : "false");
		count++;
		i = 0;
		current = current->next;
	}
}


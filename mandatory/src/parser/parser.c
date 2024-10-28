/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfortuna <mfortuna@student.42.pt>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 11:27:08 by mfortuna          #+#    #+#             */
/*   Updated: 2024/10/28 10:09:40 by mfortuna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void print_cmds(t_data *data);
int	ft_redirect(t_data *data, t_cmd *current, int y, int x)
{
	if (data->tokens[y][x] == '<')
	{
		while (data->tokens[y][x] == '<')
			x++;
		if (x > 3)
			return(ft_fprintf(2, -1, "parser error near : '<'"));
		else if (x > 1)
			current->here_doc = true;
		if (!data->tokens[++y])
			return (-1);
		current->infile = ft_strdup(data->tokens[y]);
		return (2);
	}
	while (data->tokens[y][x] == '>')
		x++;
	if (x > 2)
		return(ft_fprintf(2, -1, "parser error near : '>'"));
	else if (x > 1)
		current->appen = true;
	if (!data->tokens[++y])
		return (-1);
	current->outfile = ft_strdup(data->tokens[y]);
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
		else if (data->tokens[y][x] == '|')
		{
			if (y == 0 || data->tokens[y][1] == '|')
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
/* check for special chars not required by the subject */
int check_not_req(t_data *data)
{
	int i;

	i = 0;
	while (data->tokens[i])
	{
		if (check_chars(data->tokens[i][0]) == 2)
			return (ft_fprintf(2, 1, "parser error near '%c'\n", data->tokens[i][0]));
		i++;
	}
	return (0);
}

/* parser */
int	ft_strtok(t_data *data, int i, int j)
{
	char 	arr[1024];

	ft_memset(arr, 0, 1024);
	while (data->input[i])
	{
		while (data->input[i] <= ' ' && (data->input[i]))
			i++;
		while (check_chars(data->input[i]) > 0)
			arr[j++] = data->input[i++];
		arr[j++] = ' ';
		while (data->input[i] > ' ' && check_chars(data->input[i]) == 0)
			arr[j++] = data->input[i++];
		arr[j++] = ' ';
	}
	arr[j++] = 0;
	data->parser = ft_calloc(1024, sizeof(char));
	less_space(data, arr, 0, 0);
	split_tokens(data, 0, 0, 0);
	if (check_not_req(data) == 1)
		return (1);
	return (0);
}

int get_fullinput(t_data *data, int i)
{
	if (data->input[0] == 0)
		return (1);
	i = ft_strlen(data->input) - 1;
	while (data->input[i] == '|' || data->input[i] == ' ')
	{
		if (data->input[i] == ' ')
			i--;
		else
		{
			if (ft_strnstr(data->input, "<|", 100) || ft_strnstr(data->input, ">|", 100) || \
			ft_strnstr(data->input, "|", 1))
				return (ft_fprintf(2, 1, "parser error near '|' \n"));
			data->input = str_join(data->input, readline("> "));
			i = ft_strlen(data->input) - 1;
		}
	}
	return (0);
}

/* recives and manages input from user */
int	input_user(t_data *data)
{
	if (get_fullinput(data, 0) == 1)
		return (1);
	if (ft_strtok(data, 0, 0) == 1)
		return (1);
	create_cmds(data);
	if (parsing(data, 0, 0) == 1)
		return (1);
	if (data->cmd->cmd == NULL )
		return (1);
	// print_cmds(data);
	return (0);
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


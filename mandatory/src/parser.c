/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfortuna <mfortuna@student.42.pt>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 11:27:08 by mfortuna          #+#    #+#             */
/*   Updated: 2024/09/24 14:17:29 by mfortuna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int divide_cmds(t_cmd *current, t_data *data, int i, int start)
{
	int size;
	int	token;
	
	if (current->pipe = true)
		size = i - start;
	else
		size = (i - start) + 1;
	token = 0;
	current->full_tokens = malloc(size * sizeof(char *));
	while (start <= size)
	{
		current->full_tokens[token] = ft_strdup(data->tokens[start]);
		token++;
		start++;
	}
	return (0);
	
}
/* define each cmd */
int define_cmds(t_data *data, t_cmd *current)
{
	int	cmds;
	int	i;
	int j;

	cmds = 1;
	i = 0;
	j = 0;
	if (data->n_cmd == 1)
	{
		current->full_tokens = data->tokens;
		return (0);
	}
	while (data->tokens[i])
	{
		j = i;
		while (data->tokens[i][0] != '|' && data->tokens[i])
			i ++;
		if (data->tokens[i][0] == '|')
			divide_cmds(current, data, i, j);
		current = current->next;
	}
	return (0);
}

int	final_token_count (char **arr)
{
	int count;

	count = 0;
	while (arr[count])
		count++;
	return (count);
}

int	redirection(t_cmd *cmd, char **input, char c)
{
	int i;
	
	i = 0;
	if (c == '<')
	{
		while (input[0][i] == '<')
			i++;
		return (i);
	}
}

int cmd_line(t_cmd *cmd, char **input)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (input[i])
	{
		if (redirection(cmd, input, '<'))
	}
}
/* organize command, cmd, args input and output ... */
int org_cmds(t_data *data)
{
	/* if '<' -> infile, cmd, args 
	else cmd args
	if '>' -> next outfile*/
	t_cmd *current;
	current = data->cmd;
	int i;
	i = 0;
	while (current)
	{
		if (cmd_line(current, data->tokens) == 1)
			return (1);
		current = current->next;
	}
	return (0);
}

void count_cmds(t_data *data)
{
	char	**arr;
	int		i;
	
	i = 0;
	arr = data->tokens;
	while (arr[i])
	{
		if (arr[i][0] == '|')
			data->n_cmd++;
		i++;
	}
}

/* recives and manages input from user */
int	input_user(t_data *data)
{
	int		i;
	t_cmd	*current;

	i = 0;
	current = (*data->cmd);
	data->tokens = ft_strtok(data);
	data->n_cmd = 1;
	count_cmds(data);
	data->cmd = create_cmds(data->n_cmd);
	define_cmds(data, current);
	org_cmds(data);
}


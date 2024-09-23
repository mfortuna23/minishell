/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfortuna <mfortuna@student.42.pt>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 11:27:08 by mfortuna          #+#    #+#             */
/*   Updated: 2024/09/23 17:09:04 by mfortuna         ###   ########.fr       */
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
	current->full_cmd = malloc(size * sizeof(char *));
	while (start <= size)
	{
		current->full_cmd[token] = ft_strdup(data->tokens[start]);
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
		current->full_cmd = data->tokens;
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
		
	}
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


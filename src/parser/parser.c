/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfortuna <mfortuna@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 11:27:08 by mfortuna          #+#    #+#             */
/*   Updated: 2024/12/04 18:57:57 by mfortuna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	print_cmds(t_data *data);

int	parasing_error(t_data *data, int pipe)
{
	if (pipe == 1)
		ft_fprintf(2, 1, "parser error near '|' \n");
	data->check = 1;
	r_value(158, 1);
	return (1);
}

/* TODO nova logica
parsing entra num loop passando por todos os tokens, addiciona redirects
cmd_args tem que ter salvo SEMPRE onde ficou, adiciona argumentos as vezes 
necess]arias */
int	parsing(t_data *data, int y, int x)
{
	t_cmd	*node;

	node = data->cmd;
	while (data->tokens[y] != NULL)
	{
		if (data->tokens[y][x] == '<' || data->tokens[y][x] == '>')
			y += ft_redirect(data, node, y, 0);// pro
		else if (data->tokens[y][x] == '|')
		{
			add_last(&data->cmd);
			node->pipe = true;
			node = node->next;
			y++;
			data->n_cmd++;
			data->i = 0;
		}
		else
			y = ft_cmd_args(data, node, y, 0);
		if (y < 0)
			return (parasing_error(data, 0));
	}
	if (!node->cmd)
		data->check = 1;
	return (0);
}

int	token_error(t_data *data)
{
	data->n_tokens = token_count(data->parser, 0, 0, 0);
	data->tokens = ft_calloc((data->n_tokens + 1), sizeof(char *));
	split_tokens(data, init_iter());
	if (check_not_req(data) == 1)
	{
		free(data->parser);
		ft_freearr(data->tokens);
		data->check = 1;
		return (1);
	}
	return (0);
}

/* parser */
int	ft_strtok(t_data *data, int i, int j, char c)
{
	data->parser = ft_calloc(1024, sizeof(char));
	while (data->input[i])
	{
		if (check_chars(data->input[i]) > 0)
		{
			c = data->input[i];
			data->parser[j++] = ' ';
			data->parser[j++] = data->input[i++];
			while ((data->input[data->i] != 0) && c == data->input[i])
				data->parser[j++] = data->input[i++];
			data->parser[j++] = ' ';
		}
		else
			data->parser[j++] = data->input[i++];
	}
	return (token_error(data));
}

/* recives and manages input from user */
int	input_user(t_data *data)
{
	data->check = 0;
	data->n_cmd = 1;
	if (!data->input)
	{
		data->check = 1;
		return (-1);
	}
	if (get_fullinput(data) == 1)
		return (1);
	add_history(data->input);
	if (ft_strtok(data, 0, 0,'a') == 1)
		return (1);
	create_cmds(data);
	data->i = 0;
	if (parsing(data, 0, 0) == 1)
		return (1);
	// data->check = 1;	// TODO remove after 
	// print_cmds(data);	// remove
	// return (0);			// remove
	if (data->cmd->cmd == NULL)
		return (1);
	if (ft_exit(data, 0) == 0)
		return (-1);
	if (export_or_unset(data, data->cmd) == 0)
		data->check = 1;
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
		if (current->cmd){
		while (current->cmd[i])
			printf("%s\n", current->cmd[i++]);}
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
}
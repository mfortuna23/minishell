/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfortuna <mfortuna@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 11:34:48 by mfortuna          #+#    #+#             */
/*   Updated: 2025/01/13 19:58:53 by mfortuna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	exec_exit(t_data *data, char *path, char **cmd, char **env)
{
	char	*new_path;
	char	**new_cmd;
	char	**new_env;

	new_path = ft_strdup(path);
	new_cmd = ft_arrdup(cmd);
	new_env = ft_arrdup(env);
	ms_bomb(data, 0);
	execve(new_path, new_cmd, new_env);
	free(new_path);
	ft_freearr(new_cmd);
	ft_freearr(new_env);
	exit(0);
}

void	no_pathfound(t_data *data, t_cmd *cmd, int value)
{
	if (cmd->cmd[0])// TODO check for file or directory
		ft_fprintf(2, 0, "MS: %s: command not found\n", cmd->cmd[0]);
	if (cmd->file != NULL)
		value = 0;
	else
		value = 127;
	ms_bomb(data, 0);
	exit(value);
}

void	ft_execve(t_data *data, t_cmd *cmd)
{
	int	value;

	value = 0;
	r_value(0, 1);
	sig_inchild();
	//signal(SIGINT, SIG_DFL);
	ft_redir_all(data, cmd);
	if (cmd->builtin)
	{
		value = execute_built(data, cmd);
		ms_bomb(data, 0);
		exit(value);
	}
	if (cmd->path == NULL)
		no_pathfound(data, cmd, value);
	else
		exec_exit(data, cmd->path, cmd->cmd, data->env);
	ms_bomb(data, 0);
	exit(r_value(0, 0));
}

void	init_redic(t_data *data)
{
	t_cmd	*cmd;

	cmd = data->cmd;
	while (cmd)
	{
		cmd->in_n = data->n_cmd;
		cmd->out_n = data->n_cmd;
		cmd = cmd->next;
	}
}

int	ft_exec_pipe(t_data *data)
{
	if (!data || !data->cmd)
		return (1);
	if (ft_init_pipe(data) == 0)
		return (1);
	exec_first_command(data);
	exec_intermediate_commands(data);
	exec_last_command(data);
	close_all_pipes(data);
	return (wait_for_children(data));
}

void	set_cmds(t_data *data)
{
	t_cmd	*current;

	current = data->cmd;
	if (!current)
		return ;
	while (current)
	{
		if (check_for_built(data, current) == 0)
			current->builtin = true;
		current = current->next;
	}
	return ;
}

int	ft_execute(t_data *data, t_cmd *cmd)
{
	int status;

	(void)cmd;
	sigaction_child();
	r_value(0, 1);
	init_redic(data);
	set_cmds(data);
	if (data->n_cmd == 1)
	{
		cmd->pid = fork();
		if (cmd->pid == 0)
			ft_execve(data, cmd);
		waitpid(cmd->pid, &status, 0);
		status = WEXITSTATUS(status);
		set_up_sigaction();
		//ft_fprintf(2, 0, "this is the return value : %i", status); // TODO remove
		if (r_value(0, 0) == 130)
			return (130);
		return (status);
	}
	status = ft_exec_pipe(data);
	status = WEXITSTATUS(status);
	//ft_fprintf(2, 0, "this is the return value : %i", status);// TODO remove
	set_up_sigaction();
	if (r_value(0, 0) == 130)
		return (130);
	return (status);
}

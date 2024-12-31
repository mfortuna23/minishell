/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfortuna <mfortuna@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 11:34:48 by mfortuna          #+#    #+#             */
/*   Updated: 2024/12/31 01:06:02 by mfortuna         ###   ########.fr       */
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

void	ft_execve(t_data *data, t_cmd *cmd)
{
	int	r_value;

	sig_reset();
	ft_fprintf(1, 0, "a PID is %i\n", getpid());
	cmd->fd_in = ft_redir_in(data, cmd);
	cmd->fd_out = ft_redir_out(data, cmd);
	if (check_for_built(data, data->cmd) <= 1)
	{
		r_value = execute_built(data, cmd);
		close_fds(cmd->fd_in, cmd->fd_out);
		printf("this is builtin \n");
		ms_bomb(data, 0);
		exit(r_value);
	}
	if (cmd->path == NULL)
	{
		if (cmd->cmd[0])
			ft_fprintf(2, 0, "%s: command not found\n", cmd->cmd[0]);
		close_fds(cmd->fd_in, cmd->fd_out);
		if (cmd->here_doc)
			r_value = 0;
		else
			r_value = 127;
		ms_bomb(data, 0);
		exit (r_value);
	}
	else
		exec_exit(data, cmd->path, cmd->cmd, data->env);
	ms_bomb(data, 0);
	close_fds(cmd->fd_in, cmd->fd_out);
	exit(0);
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
	int	status;

	if (!data || !data->cmd)
		return (1);
	if (ft_init_pipe(data) == 0)
		return (1);
	exec_first_command(data);
	exec_intermediate_commands(data);
	exec_last_command(data);
	close_all_pipes(data);
	wait_for_children(data);
	// clean_pipes(data);
	return (WEXITSTATUS(status));
}

int	ft_execute(t_data *data, t_cmd *cmd)
{
	int status;

	(void)cmd;
	signal(SIGINT, SIG_IGN);
	init_redic(data);
	if (data->n_cmd == 1)
	{
		cmd->pid = fork();
		if (cmd->pid == 0)
			ft_execve(data, cmd);
		waitpid(cmd->pid, &status, 0);
		status = WEXITSTATUS(status);
		printf("this is the return value : %i", status);
		return (status);
	}
	status = ft_exec_pipe(data);
	status = WEXITSTATUS(status);
	printf("this is the return value : %i", status);
	//clean_pipes(data);
	free(data->pipe_n);
	set_up_sigaction();
	return (status);
}

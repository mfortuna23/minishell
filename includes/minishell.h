/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfortuna <mfortuna@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 11:26:18 by mfortuna          #+#    #+#             */
/*   Updated: 2025/01/07 18:37:59 by mfortuna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <sys/ioctl.h>
# include <dirent.h>
# include <signal.h>
# include <stdlib.h>

typedef struct s_data
{
	char			**env;		//env
	char			*input;		//user input
	char			*parser;	//parser
	char			**tokens;	//tokens
	char			*path;		//current directory path
	char			*prompt;
	int				n_tokens;
	int				return_v;
	int				check;
	int				i;
	int				n_cmd;
	int				**pipe_n;
	struct s_cmd	*cmd;
	struct s_env	*var;
}			t_data;

typedef struct s_env
{
	char			*full;
	char			*name;
	char			*value;
	bool			alive; // verifica se foram apagadas
	bool			w;
	struct s_env	*next;
}		t_env;

typedef struct s_cmd
{
	char				**cmd;			//final cmd
	char				*path;		//parser will not handle this
	int					in_n;			//number of inputs
	int					fd_out;
	int					fd_in;		//parser will not handle this
	int					out_n;			//number of outputs
	char				**path_to_cmd;	//path to cmd
	bool				pipe;			//more than this cmd...
	int					return_value;	// return value of this cmd
	pid_t				pid;			//parser will not handle this
	struct s_cmd		*next;			//if there is pipe else null
	struct s_infile		*in_file;
	struct s_outfile	*out_file;		//delete later
	struct s_infile		*here_doc;
	bool				builtin;
}			t_cmd;

typedef struct s_infile
{
	char			*name;
	bool			here_doc;
	char			*hd_buffer;
	struct s_infile	*next;
}			t_infile;

typedef struct s_outfile
{
	char				*name;
	bool				appen;
	struct s_outfile	*next;
}			t_outfile;

typedef struct s_iter
{
	int		i;
	int		j;
	int		x;
	int		y;
	char	c;
	bool	exp;
}			t_iter;

/****************************/
/*			READLINE		*/
/****************************/
void		rl_replace_line(const char *text, int clear_undo);

/****************************/
/*			PARSER			*/
/****************************/

int			get_cmd(t_data *data, char **env);
void		data_init(t_data *data, char **env);
char		*get_prompt(t_data *data);
void		create_env(t_data *data, char **env);
int			input_user(t_data *data);
int			parsing(t_data *data, int y, int x);
int			ft_cmd_args(t_data *data, t_cmd *node, int y, int x);
int			ft_redirect(t_data *data, t_cmd *current, int y, int x);
int			check_not_req(t_data *data);
int			ft_strtok(t_data *data, int i, int j, char c);
int			get_fullinput(t_data *data);
int			split_tokens(t_data *data, t_iter *x);
int			token_count(char *s, int i, int count, char c);
void		less_space(t_data *data, char *arr, int i, int count);
int			check_chars(char c);
int			check_not_req(t_data *data);
int			parasing_error(t_data *data, int pipe);
t_iter		*init_iter(void);
char		*ft_strdup_noquotes(t_data *data, char *old, char *new, bool exp);
bool		true_false(bool exp);

/****************************/
/*		STRUCT_CMDS.C		*/
/****************************/

void		create_cmds(t_data *data);
t_cmd		*create_node(void);
void		add_last(t_cmd **head);
void		free_mem(t_cmd *del);
void		delete_last(t_data *data);
void		delete_cmds(t_data *data);
void		add_last_outfile(t_data *data, t_outfile **head, bool ap, char *name);
void		outfile_bomb(t_outfile *head);
void		add_last_infile(t_data *data, t_infile **head, bool hd, char *name);
void		infile_bomb(t_infile *head);
t_infile	*findlast_in(t_infile **head);

/****************************/
/*		STRUCT_ENV.C		*/
/****************************/

t_env		*create_env_node(void);
void		add_last_env(t_env **head);
void		free_env(t_env *del);
void		del_lastenv(t_data *data);
t_env		*find_last_env(t_env **env);
t_env		*find_var(t_data *data, char *name);
void		del_varenv(t_data *data, char *name);
int			exist_var(t_data *data, t_env *node, char *str, char *name);

/****************************/
/*			Path			*/
/****************************/

void		free_path(char **array);
char		**get_paths(t_data *data);
char		*ft_check_command_location(t_data *data, char *command, char *path_i);
char		*relative_path(t_data *data, char *command);
char		*find_path(t_data *data, t_cmd *command);
void		set_path(t_data *data);

/****************************/
/*			EXEC			*/
/****************************/

void		clear_exit(t_data *data, int status);
void		ft_fork_exit(t_data *data);
int			ft_execute(t_data *data, t_cmd *cmd);
void		ft_execve(t_data *data, t_cmd *cmd);
void		clean_pipes(t_data *data);

/****************************/
/*			Pipes			*/
/****************************/

int			ft_exec_pipe(t_data *data);
int			ft_init_pipe(t_data *data);
void		wait_for_children(t_data *data);
void		close_all_pipes(t_data *data);
void		exec_last_command(t_data *data);
void		exec_intermediate_commands(t_data *data);
void		exec_first_command(t_data *data);
void		close_fds(int fd_in, int fd_out);
void		error_exit(char *error);
void		dup_pipes(int fd_in, int fd_out, int current, int n_cmds);

/****************************/
/*			Redic			*/
/****************************/

int			ft_redir_out(t_data *data, t_cmd *cmd);
int			ft_redir_in(t_data *data, t_cmd *cmd);

/****************************/
/*			UTILS			*/
/****************************/

int			ft_fprintf(int fd, int r_value, const char *s, ...);
void		ms_bomb(t_data *data, int check);
char		*str_join(char *s1, char *s2);
int			r_value(int value, int type);
int			data_check(t_data *data, int check, int r_value);
void		update_var(t_data *data);
char		**ft_arrdup(char **old);
void		sig_reset(void);
void		sigaction_child(void);
int			arr_count(char **arr);

/****************************/
/*			BUITINS			*/
/****************************/

int			check_for_built(t_data *data, t_cmd	*cmd);
int			export_or_unset(t_data *data, t_cmd *cmd);
int			ft_echo(t_data *data, t_cmd *cmd, int x);
int			ft_export(t_data *data, t_cmd *cmd);
int			ft_cd(t_data *data, t_cmd *cmd, int check);
int			get_heredoc(t_data *data, t_infile *infile, char *name, bool exp);
int			here_doc(t_data *data, t_infile *node, bool exp, int y);
int			hd_errors(t_data *data, char *buffer_hd, int error);
int			create_file(t_infile *file, int fd);
int			print_var(t_data *data, char *cmd, int i, int fd_out);
int			ft_exit(t_data *data, t_cmd *cmd, int i, int check);
void		set_heredoc_signals(void);
int			ft_heredoc_sig(int sig);
void		sigint_handler(int signal);
void		set_up_sigaction(void);
void		print_cmds(t_data *data);
int			count_vars(t_data *data);
int			export_no_args(t_data *data, t_cmd *cmd, int count, int n_vars);
int			execute_built(t_data *data, t_cmd *cmd);
int			ft_unset(t_data	*data, t_cmd *cmd);
int			built_flags(char **args, int echo);
int			pwd(t_data *data, t_cmd *cmd);
int			ft_cd2(t_data *data);
#endif
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariafortunato <mariafortunato@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 11:26:18 by mfortuna          #+#    #+#             */
/*   Updated: 2024/11/10 02:22:16 by mariafortun      ###   ########.fr       */
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
	struct s_cmd	*cmd;
	struct s_env	*var;
}			t_data;

typedef struct s_env
{
	char			*full;
	char 			*name;
	char 			*value;
	bool			alive; // verifica se foram apagadas. aka podemos ver as variaveis mas elas nao serao visiveis no env
	struct s_env	*next;
}		t_env;


typedef struct s_cmd
{
	char			**cmd;			//final cmd
	char			*path;			//path_to cmd
	char			**full_tokens;	//tokens from this cmd
	int				fd_in;			//parser will not handle this
	int				fd_out;			//parser will not handle this
	char			*infile;		//null if notmentioned in cmd
	char			*outfile;		//same
	bool			pipe;			//more than this cmd...
	bool			here_doc;		//if << true
	bool			appen;			//if >> true
	int				return_value;	// return value of this cmd
	pid_t			pid;			//parser will not handle this
	struct s_cmd	*next;			//if there is pipe else null
}			t_cmd;

/****************************/
/*			PARSER			*/
/****************************/

int		get_cmd(t_data *data);
void	data_init(t_data *data);
char	*get_prompt(t_data *data);
void	create_env(t_data *data);
int		input_user(t_data *data);
int 	parsing(t_data *data, int y, int x);
int		ft_cmd_args(t_data *data, t_cmd *node, int y, int x);
int		ft_redirect(t_data *data, t_cmd *current, int y, int x);
int 	check_not_req(t_data *data);
int		ft_strtok(t_data *data, int i, int j);
int 	get_fullinput(t_data *data);
int		split_tokens(t_data *data, int x, int i, int j);
int 	token_count(char *s, int i, int count, char c);
int 	less_space(t_data *data, char *arr, int i, int count);
int 	check_chars(char c);

/****************************/
/*		STRUCT_CMDS.C		*/
/****************************/

void	create_cmds(t_data *data);
t_cmd	*create_node(void);
void	add_last(t_cmd **head);
void	free_mem(t_cmd *del);
void	delete_last(t_data *data);
void	delete_cmds(t_data *data);

/****************************/
/*		STRUCT_ENV.C		*/
/****************************/

t_env	*create_env_node(void);
void	add_last_env(t_env **head);
void	free_env(t_env *del);
void	del_lastenv(t_data *data);
t_env	*find_last_env(t_env **env);
t_env	*find_var(t_data *data, char *name);
void	del_varenv(t_data *data, char *name);

/****************************/
/*			EXEC			*/
/****************************/

int		ft_execute(t_data *data); // E preciso verificar se tem buitins quando chega nesta funcao mas serao ignorados

/****************************/
/*			UTILS			*/
/****************************/

int		ft_fprintf(int fd, int r_value, const char *s, ...);
void	ms_bomb(t_data *data);
char	*str_join(char *s1, char *s2);

/****************************/
/*			BUITINS			*/
/****************************/

int		check_for_built(t_data *data, t_cmd	*cmd);
int 	ft_echo(t_data *data, char **cmd, int x, int y);
int		ft_export(t_data *data);


#endif
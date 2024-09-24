/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfortuna <mfortuna@student.42.pt>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 11:26:18 by mfortuna          #+#    #+#             */
/*   Updated: 2024/09/24 11:45:40 by mfortuna         ###   ########.fr       */
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
	char			**env;
	char			*input;
	char			**tokens;
	char			*path;
	char			*prompt;
	int				n_cmd;
	struct s_cmd	**cmd;
}			t_data;

typedef struct s_cmd
{
	char			**cmd;		//final cmd
	char			*path;		//path_to cmd
	char			**full_tokens; //tokens from this cmd
	int				fd_in;		//parser will not handle this
	int				fd_out;		//parser will not handle this
	char			*infile;	//null if notmentioned in cmd
	char			*outfile;	//same
	bool			pipe;		//more than this cmd...
	bool			here_doc;	//if << true
	bool			appen;		//if >> true
	pid_t			pid;		//parser will not handle this
	struct s_cmd	*next;		//if there is pipe else null
}			t_cmd;

char	**ft_fullcmd(char *cmd);
char	*find_path(char *cmd, char **env);
t_cmd	**create_cmds(int n);
void	 add_last(t_cmd **head);
t_cmd	*create_node(void);
int		input_user(t_data *data);
int		ft_strtok(t_data *data);

#endif
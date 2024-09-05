/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfortuna <mfortuna@student.42.pt>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 11:26:18 by mfortuna          #+#    #+#             */
/*   Updated: 2024/09/05 12:19:15 by mfortuna         ###   ########.fr       */
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
	char			**full_cmd;
	char			*path;
	char			*prompt;
	int				n_cmd;
	struct s_cmd	**cmd;
	
}			t_data;

typedef struct s_cmd
{
	char			*cmd;
	char			*path;
	char			**full_cmd;
	char			*args;
	int				fd_in;
	int				fd_out;
	char			*infile;
	char			*outfile;
	bool			pipe;
	pid_t			pid;
	struct s_cmd	*next;
}			t_cmd;

char	**ft_fullcmd(char *cmd);
char	*find_path(char *cmd, char **env);
t_cmd	**create_cmds(int n);
void	 add_last(t_cmd **head);
t_cmd	*create_node(void);

#endif
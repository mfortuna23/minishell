# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mfortuna <mfortuna@student.42.pt>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/21 11:05:07 by mfortuna          #+#    #+#              #
#    Updated: 2024/11/18 11:43:16 by mfortuna         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.INCLUDEDIRS	: /mandatory /libft

UNAME_S := $(shell uname -s)

ifeq ($(UNAME_S),Linux)
    RUN_MS = valgrind -q --leak-check=full --show-leak-kinds=all --suppressions=ignore_readline_leaks.supp --track-fds=yes ./$(NAME)
else ifeq ($(UNAME_S),Darwin)
    RUN_MS = leaks -atExit -- ./$(NAME)
endif

CC				= cc
CFLAGS 			= -Wall -Werror -Wextra -g -I/usr/local/opt/readline/include
LDFLAGS 		= -L/usr/local/opt/readline/lib -lreadline -lncurses
RM				= rm -rf
NAME			= minishell
LIBFT_PATH		= $(INCLUDES)libft/
NAMELIB			= $(INCLUDES)libft/libft.a
INCLUDES		= includes/
SRC_M			= src/
EXEC			= $(addprefix $(SRC_M)exec/, cmd_path.c ft_execute.c free_aux.c redir.c pipe.c path_aux.c pipe_aux.c)
PARSER			= $(addprefix $(SRC_M)parser/, parser.c parser_utils.c 1st_step.c built_cmds.c full_input.c)
STRUCT			= $(addprefix $(SRC_M)struct/, struct_cmds.c struct_env.c delete_env.c find_env.c)
UTILS			= $(addprefix $(SRC_M)utils/, utils.c ft_fprintf.c)
BUILT			= $(addprefix $(SRC_M)builtins/, builtins.c export.c echo.c heredoc.c exit.c)
SRC				= $(SRC_M)main.c $(EXEC) $(PARSER) $(STRUCT) $(UTILS) $(BUILT)
ODIR			= obj
OBJS			= $(patsubst $(SRC_M)%.c,$(ODIR)/%.o,$(SRC)) 
MAKE			= make -C


all: $(NAME) 

$(NAME) : $(OBJS) $(NAMELIB)
	$(CC) -g $(CFLAGS) -o $(NAME) $(SRC) $(NAMELIB) $(LDFLAGS)

$(NAMELIB) : $(LIBFT_PATH)
	$(MAKE) $(LIBFT_PATH)

$(ODIR)/%.o: $(SRC_M)/%.c | $(ODIR)
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -g -I . -c $< -o $@

$(ODIR):
	mkdir -p $(ODIR)

leaks : $(NAME)
	$(RUN_MS)

clean:
	${RM} ${ODIR}
	${RM} minishell.dSYM
	$(MAKE) $(LIBFT_PATH) clean

fclean: clean
	$(RM) $(NAME)
	$(RM) $(NAMELIB)

re: fclean all

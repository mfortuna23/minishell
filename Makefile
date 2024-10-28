# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mfortuna <mfortuna@student.42.pt>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/21 11:05:07 by mfortuna          #+#    #+#              #
#    Updated: 2024/10/28 11:48:41 by mfortuna         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.INCLUDEDIRS	: /mandatory /libft

CC				= cc
CFLAGS			= -Wall -Werror -Wextra 
RM				= rm -rf
NAME			= minishell
LIBFT_PATH		= $(INCLUDES)libft/
NAMELIB			= $(INCLUDES)libft/libft.a
INCLUDES		= includes/
SRC_M			= src/
EXEC			= $(addprefix $(SRC_M)exec/, cmd_path.c ft_execute.c)
PARSER			= $(addprefix $(SRC_M)parser/, parser.c parser_utils.c 1st_step.c)
STRUCT			= $(addprefix $(SRC_M)struct/, struct_cmds.c struct_env.c)
UTILS			= $(addprefix $(SRC_M)utils/, utils.c ft_fprintf.c)
BUILT			= $(addprefix $(SRC_M)builtins/, builtins.c)
SRC				= $(SRC_M)main.c $(EXEC) $(PARSER) $(STRUCT) $(UTILS) $(BUILT)
ODIR			= obj
OBJS			= $(patsubst $(SRC_M)%.c,$(ODIR)/%.o,$(SRC)) 
MAKE			= make -C


all: $(NAME) 

$(NAME) : $(OBJS) $(NAMELIB)
	$(CC) -g $(CFLAGS) -o $(NAME) $(SRC) $(NAMELIB) -lreadline
	valgrind -q --leak-check=full --show-leak-kinds=all --suppressions=ignore_readline_leaks.supp --track-fds=yes ./$(NAME)

$(NAMELIB) : $(LIBFT_PATH)
	$(MAKE) $(LIBFT_PATH)

$(ODIR)/%.o: $(SRC_M)/%.c | $(ODIR)
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -g -I . -c $< -o $@

$(ODIR):
	mkdir -p $(ODIR)

clean:
	${RM} ${ODIR}
	$(MAKE) $(LIBFT_PATH) clean

fclean: clean
	$(RM) $(NAME)
	$(RM) $(NAMELIB)

re: fclean all

# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mfortuna <mfortuna@student.42.pt>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/21 11:05:07 by mfortuna          #+#    #+#              #
#    Updated: 2024/10/25 10:44:59 by mfortuna         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.INCLUDEDIRS	: /mandatory /libft

CC				= cc
CFLAGS			= -Wall -Werror -Wextra 
RM				= rm -rf
NAME			= minishell
LIBFT_PATH		= $(MANDATORY)libft/
NAMELIB			= $(MANDATORY)libft/libft.a
MANDATORY		= mandatory/
SRC_M			= $(MANDATORY)src/
SRC				= $(addprefix $(SRC_M), main.c cmd_path.c parser.c \
 parser_utils.c struct_cmds.c ft_fprintf.c utils.c struct_env.c)
OBJS			= $(SRC:%.c=%.o)
AR				= ar rc
MAKE			= make -C


all: $(NAME) 

$(NAME) :  $(OBJS) $(NAMELIB)
	$(CC) -g $(CFLAGS) -o $(NAME) $(SRC) $(LIBFT_PATH)ft_strnstr.c $(NAMELIB) -lreadline
	valgrind -q --leak-check=full --show-leak-kinds=all --suppressions=ignore_readline_leaks.supp --track-fds=yes ./$(NAME)

$(NAMELIB) : $(LIBFT_PATH)
	$(MAKE) $(LIBFT_PATH)

$(SRC_M)%.o: %.c
	$(CC) $(CFLAGS) -g -I . -c $<

clean:
	$(RM) $(SRC_M)*.o
	$(MAKE) $(LIBFT_PATH) clean

fclean: clean
	$(RM) $(NAME)
	$(RM) $(NAMELIB)

re: fclean all

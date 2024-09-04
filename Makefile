# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mfortuna <mfortuna@student.42.pt>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/21 11:05:07 by mfortuna          #+#    #+#              #
#    Updated: 2024/09/04 15:35:38 by mfortuna         ###   ########.fr        #
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
SRC				= $(addprefix $(SRC_M), main.c cmd_path.c)
OBJS			= $(SRC:%.c=%.o)
AR				= ar rc
MAKE			= make -C


all: $(NAME) 

$(NAME) :  $(OBJS) $(NAMELIB)
	$(CC) -g $(CFLAGS) -o $(NAME) $(SRC) $(NAMELIB) -lreadline

$(NAMELIB) : $(LIBFT_PATH)
	$(MAKE) $(LIBFT_PATH)

$(SRC_M)%.o: %.c
	$(CC) $(CFLAGS) -I . -c $<

clean:
	$(RM) $(SRC_M)*.o
	$(MAKE) $(LIBFT_PATH) clean

fclean: clean
	$(RM) $(NAME)
	$(RM) $(NAMELIB)

re: fclean all

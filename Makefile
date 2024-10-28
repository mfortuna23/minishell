# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mfortuna <mfortuna@student.42.pt>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/21 11:05:07 by mfortuna          #+#    #+#              #
#    Updated: 2024/10/28 10:35:35 by mfortuna         ###   ########.fr        #
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
EXEC			= $(addprefix $(SRC_M)exec/, cmd_path.c)
PARSER			= $(addprefix $(SRC_M)parser/, parser.c parser_utils.c)
STRUCT			= $(addprefix $(SRC_M)struct/, struct_cmds.c struct_env.c)
UTILS			= $(addprefix $(SRC_M)utils/, utils.c ft_fprintf.c)
SRC				= $(SRC_M)main.c $(EXEC) $(PARSER) $(STRUCT) $(UTILS)
ODIR			= obj
OBJS			= $(patsubst %.c,$(ODIR)/%.o,$(SRC))
MAKE			= make -C


all: $(NAME) 

$(NAME) :  $(OBJS) $(NAMELIB)
	$(CC) -g $(CFLAGS) -o $(NAME) $(SRC) $(LIBFT_PATH)ft_strnstr.c $(NAMELIB) -lreadline
	valgrind -q --leak-check=full --show-leak-kinds=all --suppressions=ignore_readline_leaks.supp --track-fds=yes ./$(NAME)

$(NAMELIB) : $(LIBFT_PATH)
	$(MAKE) $(LIBFT_PATH)

$(ODIR)/%.o: $(SDIR)/%.c | $(ODIR)
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -g -I . -c $<

clean:
	$(RM) $(SRC_M)*.o
	${RM} ${ODIR}
	$(MAKE) $(LIBFT_PATH) clean

fclean: clean
	$(RM) $(NAME)
	$(RM) $(NAMELIB)

re: fclean all

# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sdos-san <sdos-san@student.42.rio>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/13 18:00:02 by rasilva           #+#    #+#              #
#    Updated: 2023/01/09 14:31:35 by sdos-san         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	minishell

LIBFTPRINTF	=	./ft_printf/libftprintf.a

CFLAGS	=	-g -Wall -Werror -Wextra

SRCS	=	utils_checkers.c minishell.c utils_len.c \
			utils_print_env.c parser.c freedom_sings.c expansions.c expansions_dir.c \
			nodes.c here_docs.c get_files.c cmd_builtins.c execution.c \
			exec_cmd.c prompt.c

OBJS	=	$(SRCS:.c=.o)

LDFLAGS = -L /usr/local/opt/readline/lib
LDFLAGS += -L ~/.brew/opt/readline/lib
CPPFLAGS = -I /usr/local/opt/readline/include
CPPFLAGS += -I ~/.brew/opt/readline/include

%.o: %.c 
	@ $(CC) $(CFLAGS) -c $< -o $@ 

$(NAME):	$(OBJS)
		@ make -s -C ./ft_printf
		@ cc $(OBJS) -o $(NAME) $(LIBFTPRINTF) -lreadline $(CPPFLAGS) $(LDFLAGS)
		@echo ">> Minishell Compiled 🐚"
		@echo ">> OK ✅"

all:		$(NAME)

valgrind: 	all
			valgrind --leak-check=full --show-reachable=yes --show-leak-kinds=all --error-limit=no --gen-suppressions=all --log-file=lib.log ./$(NAME)

clean:
		@ rm -f $(OBJS)
		@ make clean -s -C ./ft_printf
		@echo ">> All clean 🗑️"
		
fclean:		clean
		@ rm -f $(NAME)
		@ make fclean -s -C ./ft_printf

re:		fclean all

.PHONY:		all clean fclean re

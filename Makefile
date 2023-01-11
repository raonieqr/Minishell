# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sdos-san < sdos-san@student.42.rio >       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/13 18:00:02 by rasilva           #+#    #+#              #
#    Updated: 2023/01/11 11:01:03 by sdos-san         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=minishell

SRCS	=	utils_checkers.c minishell.c utils_len.c \
			utils_print_env.c parser.c freedom_sings.c expansions.c expansions_dir.c \
			nodes.c here_docs.c get_files.c cmd_builtins.c execution.c \
			exec_cmd.c prompt.c \

LIBFT = ft_printf/libftprintf.a

OBJ    = $(SRCS:.c=.o)

detected_OS := $(shell uname)
ifeq ($(detected_OS),Linux)
LDFLAGS = -L /usr/local/opt/readline/lib
CPPFLAGS = -I /usr/local/opt/readline/include
else
CPPFLAGS += -I ~/.brew/opt/readline/include
LDFLAGS += -L ~/.brew/opt/readline/lib
endif

$(NAME): $(OBJ)
	@make -s -C ft_printf/
	@cc -g -Wall -Wextra -Werror $(SRCS) -o $(NAME) $(LIBFT) -lreadline $(CPPFLAGS) $(LDFLAGS)

all: $(NAME)

clean:
	@make clean -s -C ft_printf/
	@rm -f $(OBJ)

fclean: clean
	@make fclean -s -C ft_printf/
	@rm -rf $(NAME)

re:    fclean all

.PHONY:    all clean fclean re norminette

valgrind: all
	valgrind --leak-check=full --show-reachable=yes --show-leak-kinds=all --error-limit=no --gen-suppressions=all --track-origins=yes  --log-file=lib.log ./minishell


# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: marvin <marvin@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/13 18:00:02 by rasilva           #+#    #+#              #
#    Updated: 2023/01/16 23:38:14 by marvin           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SHELL			= /bin/bash

NAME=minishell
RM = rm -rf

#Styles
SET_COLOR	= \033[0:39m
RED				= \033[0;31m
GREEN			= \033[0;32m
YELLOW		= \033[0;33m
BLUE			= \033[0;34m
MAGENTA		= \033[0;35m
CYAN			= \033[0;36m
GRAY			= \033[0;90m
L_RED			=	\033[0;91m
L_GREEN		=	\033[0;92m
L_YELLOW	=	\033[0;93m
L_BLUE		=	\033[0;94m
L_MAGENTA	=	\033[0;95m
L_CYAN		=	\033[0;96m
WHITE			= \033[0;97m
BG_GREEN	= \033[42;1;37m

SRCS	=	utils_checkers.c minishell.c utils_len.c config_cmd.c utils_nodes.c\
			utils_print_env.c parser.c freedom_sings.c expansions.c expansions_dir.c \
			nodes.c here_docs.c get_files.c cmd_builtins.c execution.c expand_var.c\
			exec_cmd.c prompt.c copy_envp.c parser_2.c builtin.c signals.c pipe.c\

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
	@$(RM) $(OBJ)
	@echo -e -n "$(MAGENTA)[MINISHELL]:$(SET_COLOR)$(BLUE) Object files$(SET_COLOR)$(GREEN)  => Cleaned$(SET_COLOR)"
	@echo -e " 🗑️$(SET_COLOR)"

fclean: clean
	@make fclean -s -C ft_printf/
	@$(RM) $(NAME)
	@$(RM) minishell.log
	@echo -e -n "$(MAGENTA)[MINISHELL]:$(SET_COLOR)$(BLUE) Executable file$(GREEN)  => Cleaned$(SET_COLOR)"
	@echo -e " 🗑️$(SET_COLOR)"

re:    fclean all
	@echo -e "\n$(GREEN) => Cleaned and rebuilt everything <= $(SET_COLOR)"

valgrind: all
	valgrind --leak-check=full --show-reachable=yes --show-leak-kinds=all --error-limit=no --gen-suppressions=all --track-origins=yes  --log-file=minishell.log ./minishell

.PHONY:    all clean fclean re

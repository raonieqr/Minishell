# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sdos-san <sdos-san@student.42.rio>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/13 18:00:02 by rasilva           #+#    #+#              #
#    Updated: 2022/12/28 14:54:41 by sdos-san         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	minishell

LIBFTPRINTF	=	./ft_printf/libftprintf.a

CFLAGS	=	-g -Wall -Werror -Wextra

SRCS	=	utils_checkers.c minishell.c utils_len.c \
			utils_print_env.c parser.c freedom_sings.c expansions.c expansions_dir.c

OBJS	=	$(SRCS:.c=.o)

LDFLAGS = -L ~/.brew/opt/readline/lib
CPPFLAGS = -I ~/.brew/opt/readline/include

%.o: %.c 
	@ $(CC) $(CFLAGS) -c $< -o $@ 

$(NAME):	$(OBJS)
		@ make -s -C ./ft_printf
		@ cc $(OBJS) -o $(NAME) $(LIBFTPRINTF) -lreadline $(CPPFLAGS) $(LDFLAGS)
		@echo ">> Minishell Compiled 🐚"
		@echo ">> OK ✅"

all:		$(NAME)

clean:
		@ rm -f $(OBJS)
		@ make clean -s -C ./ft_printf
		@echo ">> All clean 🗑️"
		
fclean:		clean
		@ rm -f $(NAME)
		@ make fclean -s -C ./ft_printf

re:		fclean all

.PHONY:		all clean fclean re

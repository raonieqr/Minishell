# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rasilva <rasilva@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/13 18:00:02 by rasilva           #+#    #+#              #
#    Updated: 2022/12/16 16:21:42 by rasilva          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	minishell

LIBFTPRINTF	=	./ft_printf/libftprintf.a

CFLAGS	=	-g -Wall -Werror -Wextra

SRCS	=	utils.c minishell.c

OBJS	=	$(SRCS:.c=.o)

%.o: %.c 
	@ $(CC) $(CFLAGS) -c $< -o $@

$(NAME):	$(OBJS)
		@ make -s -C ./ft_printf
		@ cc $(OBJS) -o $(NAME) $(LIBFTPRINTF)
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

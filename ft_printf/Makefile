# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rasilva <rasilva@student.42.rio>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/06 15:34:37 by rasilva           #+#    #+#              #
#    Updated: 2022/10/13 17:56:25 by rasilva          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= libftprintf.a
CC	= gcc
CFLAGS	= -Wall -Wextra -Werror
AR	= ar rcs
RM	= rm -f

LIBRARY = ./libft/

SRC	= ft_printf.c ft_hex.c ft_address.c ft_printf_utils.c

OBJS	= $(SRC:.c=.o)

.c.o:	
	$(CC) $(CFLAGS) -I $(LIBRARY) -c $< -o $(<:.c=.o)

$(NAME):	$(OBJS)
	cd $(LIBRARY) && $(MAKE) && cp libft.a ../$(NAME)
		$(AR) $(NAME) $(OBJS)
		ranlib $(NAME)
		@echo ">> Libft Printf Compiled 📚"

all:	$(NAME)

clean:
	$(RM) $(OBJS)
	cd $(LIBRARY) && $(MAKE) clean

fclean:	clean
	$(RM) $(NAME) 
	cd $(LIBRARY) && $(MAKE) fclean

re:	fclean all

.PHONY: all clean fclean re


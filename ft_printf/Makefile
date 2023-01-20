# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sdos-san <sdos-san@student.42.rio>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/19 13:48:03 by sdos-san          #+#    #+#              #
#    Updated: 2023/01/19 13:48:06 by sdos-san         ###   ########.fr        #
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


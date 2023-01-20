# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sdos-san <sdos-san@student.42.rio>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/19 13:55:03 by sdos-san          #+#    #+#              #
#    Updated: 2023/01/19 13:55:06 by sdos-san         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= libft.a
CC	= gcc
CFLAGS	= -Wall -Wextra -Werror
AR	= ar rcs
RM	= rm -f

INCS	= libft.h
SRC	= \
	ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c \
	ft_isprint.c ft_strlen.c ft_memset.c ft_bzero.c \
	ft_memcpy.c ft_memmove.c ft_strlcpy.c ft_strlcat.c \
	ft_toupper.c ft_tolower.c ft_strchr.c ft_strrchr.c \
	ft_strncmp.c ft_memchr.c ft_memcmp.c ft_strnstr.c \
	ft_atoi.c ft_calloc.c ft_strdup.c ft_substr.c \
	ft_strjoin.c ft_strtrim.c ft_split.c ft_itoa.c \
	ft_strmapi.c ft_striteri.c ft_putchar_fd.c ft_putstr_fd.c \
	ft_putendl_fd.c ft_putnbr_fd.c ft_utoa.c ft_lstadd_back_bonus.c \
	ft_lstadd_front_bonus.c ft_lstdelone_bonus.c ft_lstiter_bonus.c  ft_lstclear_bonus.c\
	ft_lstlast_bonus.c ft_lstmap_bonus.c ft_lstnew_bonus.c ft_lstsize_bonus.c \

OBJS	= $(SRC:.c=.o)

.c.o:	
		$(CC) $(CFLAGS) -c $< -o $(<:.c=.o)

$(NAME):	$(OBJS) $(INCS)
			$(AR) $(NAME) $(OBJS)
			ranlib $(NAME)

all:	$(NAME)

clean:
		$(RM) $(OBJS)

fclean:	clean
		$(RM) $(NAME) 

re:	fclean all

.PHONY: all clean fclean re

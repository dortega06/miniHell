# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: diespino <diespino@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/15 17:16:03 by diespino          #+#    #+#              #
#    Updated: 2025/12/10 14:27:14 by diespino         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

SRC = 	\
	ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c\
	ft_strlen.c ft_memset.c ft_bzero.c ft_memcpy.c ft_memmove.c\
	ft_strlcpy.c ft_strlcat.c ft_toupper.c ft_tolower.c ft_strchr.c\
	ft_strrchr.c ft_strncmp.c ft_memchr.c ft_memcmp.c ft_strnstr.c\
	ft_atoi.c ft_calloc.c ft_strdup.c ft_substr.c ft_strjoin.c\
	ft_strtrim.c ft_split.c ft_itoa.c ft_strmapi.c ft_striteri.c\
	ft_putchar_fd.c	ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c\
	ft_strcmp.c ft_isspace.c ft_isquote.c ft_memfree.c ft_memfree_all.c\
	\
	ft_printf.c\
	ft_printf_nbr.c\
	ft_printf_hex.c\
	ft_printf_ptr.c

OBJS = $(SRC:.c=.o)
DEPS = $(SRC:.c=.d)

INCS = includes

RM = rm -f

CC = gcc
CLIB = ar rcs
CFLAGS = -Wall -Wextra -Werror -I

$(NAME): $(OBJS)
	$(CLIB) $(NAME) $(OBJS)

%.o: %.c Makefile
	$(CC) $(CFLAGS) $(INCS) -MMD -MP -c $< -o $@
	
-include $(DEPS)

all: $(NAME)

clean:
	$(RM) $(OBJS)
	$(RM) $(DEPS)
	
fclean: clean
	$(RM) $(NAME)
	
re: fclean all

print_src:
	@echo $(SRC)

.PHONY: all clean fclean re print_src

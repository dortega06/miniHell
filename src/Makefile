# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: diespino <diespino@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/10/10 14:04:02 by diespino          #+#    #+#              #
#    Updated: 2025/11/25 16:32:41 by diespino         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Output NAME
NAME = minisHell

# miniHell SRCs
MAIN		= main.c

LEXER_PATH	= lexer
LEXER		= $(LEXER_PATH)/lexer.c\
		  $(LEXER_PATH)/lexer_syntax.c\
		  $(LEXER_PATH)/lexer_utils.c\
		  $(LEXER_PATH)/treat_tokens.c\
		  $(LEXER_PATH)/lexer_var.c
		  #$(LEXER_PATH)/main.c# main lexer

PARSER_PATH	= #parser
PARSER		= #$(PARSER_PATH)/fill_node.c\
		  #$(PARSER_PATH)/fill_utils.c\
		  #$(PARSER_PATH)/parser.c\
		  #$(PARSER_PATH)/parser_utils.c\
		  #$(PARSER_PATH)/heredoc.c
		  #$(PARSER_PATH)/main_fill.c# main lexer + parser

UTILS_PATH	= utils
UTILS		= $(UTILS_PATH)/env_utils.c

OBJS		= $(MAIN:.c=.o) $(LEXER:.c=.o) $(PARSER:.c=.o) $(UTILS:.c=.o)
DEPS		= $(MAIN:.c=.d) $(LEXER:.c=.d) $(PARSER:.c=.d) $(UTILS:.c=.d)

INCS		= ../includes

# LIBFT
LIBFT_PATH	= ../libft
LIBFT		= $(LIBFT_PATH)/libft.a
LIBFT_SRC	:= $(addprefix $(LIBFT_PATH)/, \
		   $(shell make -sC $(LIBFT_PATH) print_src))

# Flags
CC	 	= gcc
CLIB 		= ar rcs
CFLAGS 		= -Wall -Wextra -Werror
RM 		=  rm -f

# Colors ANSI 	  \033[<color;estilo_letra>\033[0m
END 		= \033[0m
RED		= \033[31;1m
GREEN		= \033[32;1m
YELLOW		= \033[33;1m
MAGENTA		= \033[35;1m
CIAN		= \033[36m


all: $(LIBFT) $(NAME)

# Compilacion LIBFT
$(LIBFT): $(LIBFT_PATH)/Makefile $(LIBFT_PATH)/libft.h $(LIBFT_SRC)
	@echo -n "--> Building $(MAGENTA)[LIBFT]$(END)... "
	@make -sC $(LIBFT_PATH)
	@echo "$(GREEN)DONE!$(END)"

# Compilacion miniHell
$(NAME): $(OBJS) $(LIBFT) $(INCS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -lreadline -o $(NAME)

# Compilacion de *.c en *.o && *.d
%.o: %.c Makefile
	$(CC) $(CFLAGS) -I $(INCS) -MMD -MP -c $< -o $@

# Dependecies .d
-include $(DEPS)

clean:
	$(RM) $(OBJS)
	$(RM) $(DEPS)
	make clean -C $(LIBFT_PATH)

fclean: clean
	$(RM) $(NAME)
	$(RM) $(LIBFT)

re: fclean all

.PHONY: all clean fclean re

# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: diespino <diespino@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/10/10 14:04:02 by diespino          #+#    #+#              #
#    Updated: 2025/12/21 19:17:48 by dortega-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Output NAME
NAME = minishell

# miniHell SRCs
MAIN		= main.c\
		  print_tests.c

LEXER_PATH	= lexer
LEXER		= $(LEXER_PATH)/lexer.c\
		  $(LEXER_PATH)/lexer_syntax.c\
		  $(LEXER_PATH)/lexer_utils.c\
		  $(LEXER_PATH)/treat_tokens.c\
		  $(LEXER_PATH)/lexer_var.c
		  #$(LEXER_PATH)/main.c# main lexer

PARSER_PATH	= parser
PARSER		= $(PARSER_PATH)/fill_node.c\
		  $(PARSER_PATH)/fill_redir.c\
		  $(PARSER_PATH)/parser.c\
		  $(PARSER_PATH)/parser_utils.c\
		  $(PARSER_PATH)/heredoc.c
		  #$(PARSER_PATH)/main_fill.c# main lexer + parser

EXEC_PATH	= exec
EXEC		= $(EXEC_PATH)/ft_exec.c\
		  $(EXEC_PATH)/exec_utils.c\
		  $(EXEC_PATH)/signal.c\
		  $(EXEC_PATH)/split_shell.c

BUILTIN_PATH	= built_ins
BUILTIN		= $(BUILTIN_PATH)/builtins.c\
		  $(BUILTIN_PATH)/ft_env.c\
		  $(BUILTIN_PATH)/ft_export.c\
		  $(BUILTIN_PATH)/export_utils.c\
		  $(BUILTIN_PATH)/ft_unset.c\
		  $(BUILTIN_PATH)/ft_exit.c\
		  $(BUILTIN_PATH)/ft_echo.c\
		  $(BUILTIN_PATH)/ft_pwd.c\
		  $(BUILTIN_PATH)/ft_cd.c\
		  $(BUILTIN_PATH)/cd_utils.c


UTILS_PATH	= utils
UTILS		= $(UTILS_PATH)/env.c \
		  $(UTILS_PATH)/env_utils.c

SRC		= $(LEXER) $(PARSER) $(EXEC) $(BUILTIN)
OBJS		= $(MAIN:.c=.o) $(SRC:.c=.o) $(UTILS:.c=.o)
DEPS		= $(MAIN:.c=.d) $(SRC:.c=.d) $(UTILS:.c=.d)

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

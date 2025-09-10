/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diespino <diespino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 13:01:04 by diespino          #+#    #+#             */
/*   Updated: 2025/09/10 16:25:20 by diespino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <string.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <sys/ioctl.h>
# include <signal.h>
# include <termios.h>
# include <termcap.h>
# include "../libft/includes/libft.h"

typedef enum token_type
{
	WORD,//		cmd, args, etc
	PIPE,//		|
	REDIR_IN,//	<
	REDIR_OUT,//	>
	APPEND,// 	>>
	HEREDOC,// 	<<
	ERROR,
} 	t_token_type;

typedef struct s_token
{
	t_token_type	type;// WORD, PIPE,...
	char			*value;// palabra o simbolo
	int				position;// posicion palabra
	struct s_token	*next;
}			t_token;

typedef struct s_parser {
    t_token	*token;    // Lista enlazada en lugar de array
    t_token	*current_node;  // Nodo actual en lugar de índice
    bool	has_error;
    char	*error_message;
} t_parser;

// TOKEN UTILS
int		is_quotes(char c);
t_token_type	is_symbol(char *str);

#endif

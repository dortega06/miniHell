/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diespino <diespino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 13:01:04 by diespino          #+#    #+#             */
/*   Updated: 2025/10/15 19:27:06 by dortega-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
/*═══════════════════════════ [  VAR GLOBAL  ] ═══════════════════════════════*/

extern int	g_signal;

/*═════════════════════════════ [  LIBS  ] ═══════════════════════════════════*/
# include "../libft/libft.h"
//global libs
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

/*═══════════════════════════ [  MACROS  ] ════════════════════════════════════*/

# define ERR_TOKEN "minishell: syntax error near unexpected token"
# define ERR_PIPE "minishell: failed to open pipe"
# define ERR_FORK "minishell: fork failed"
/*═══════════════════════════ [  ENUMS  ] ════════════════════════════════════*/

typedef enum e_token
{
	T_GENERAL,
	T_CMD,       // comando
	T_PIPE,      // | pipe
	T_REDIR_IN,  // < REDIR_IN
	T_INFILE,    // infile
	T_HEREDOC,   // << HEREDOC
	T_LIMITER,   // (str) para terminar de introducir datos
	T_REDIR_OUT, // > REDIR_OUT
	T_OUTFILE,   // outfile
	T_APPEND,    // >> APPEND
	T_SIZE
}			t_token_type;

typedef enum e_signal
{
	S_BASE,
	S_HEREDOC,
	S_HEREDOC_END
}			t_signal;

/*══════════════════════════ [  STRUCTS  ] ═══════════════════════════════════*/

typedef struct s_lexer
{
	int				index; //  indice del token
	char			*data; //  contenido (valor literal)
	int				type;  //  numero equivalente al token (enum)
	struct s_lexer	*next; //  siguiente elemento en la lista
}	t_lexer;
/*
typedef struct s_env
{
	char *var_name;     // nombre de la variable
	char *value_var;    // valor de la variable
	struct s_env *next; //  siguiente elemento en la lista
}			t_env;*/

typedef struct s_parser
{
	char *cmd;             // comando que será ejecutado
	int redir_in;          // redireccionamiento de entrada
	int redir_out;         // redireccionamiento de salida
	struct s_parser *next; //  siguiente elemento en la lista
}			t_parser;

typedef struct s_shell
{
	char **paths;       // variables de entorno del sistema
	char **cmd_args;    // comando seguido de argumentos
	int count_cmd_args; // cantidad de comando + argumentos
//	t_env *env;         // lista de nodos que representa `envp`
	t_lexer *lexer;     // lista de nodos que separa los tokens
	t_parser *parser;   // lista de nodos que separa los comandos
	int exit_status;    // entero que representa el estado de salida
}			t_shell;

/*═════════════════════════ [  FUNCTIONS  ] ══════════════════════════════════*/
/*---------------------------- [  lexer  ] -----------------------------------*/
int		ft_isspace(int c);
int		get_type(char *str, int i);

void	ft_lexer(char *input, t_lexer **lexer);

int	check_syntax(t_lexer *lexer);
//int	check_syntax_pipe(t_lexer *lexer);

//void	lexer_add_type(t_lexer **lexer, int type);
void	lexer_add_token(char *str, t_lexer **lexer, int *i, int size, int type);

int		treat_quotes(char *input, t_lexer **lexer, int *i, int type);
void    treat_general(char *input, t_lexer **lexer, int *i, int type);
void    treat_special(char *input, t_lexer **lexer, int *i, int type);

void	free_token_lst(t_lexer **lexer);

/*--------------------------- [  parser  ] -----------------------------------*/
t_lexer	*find_start_node(t_lexer *lex, int start);
void	process_redirections(t_lexer *start_node, t_parser **cmd_node, int *start, int end);
void	fill_redir(t_lexer *lex, t_parser **cmd_node, int *start, int end);
void	ft_fill_node(t_lexer *lex, t_parser **cmd_node, int start, int end);
void	ft_redirect(t_lexer *tmp, t_parser **cmd_node);
void	fill_cmd(t_lexer *tmp, t_parser **cmd_node);
int	ft_len_cmd(t_lexer *tmp);
#endif

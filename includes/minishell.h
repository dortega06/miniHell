/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diespino <diespino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 13:01:04 by diespino          #+#    #+#             */
/*   Updated: 2025/09/20 16:43:01 by dortega-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

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
}			t_token;

/*══════════════════════════ [  STRUCTS  ] ═══════════════════════════════════*/

typedef struct s_lexer
{
	int				index; //  indice del token
	char			*data; //  contenido (valor literal)
	int				type;  //  numero equivalente al token (enum)
	struct s_lexer	*next; //  siguiente elemento en la lista
}	t_lexer;

typedef struct s_env
{
	char *var_name;     // nombre de la variable
	char *value_var;    // valor de la variable
	struct s_env *next; //  siguiente elemento en la lista
}			t_env;

typedef struct s_parser
{
	char			*cmd; //comando que será ejecutado
	int 			redir_in; //entrada
	int 			redir_out; //salida
	struct s_parser	*next; //siguiente elemento en la lista
}	t_parser;

typedef struct s_arg
{
    char *arg;
    struct s_arg *next;
} t_arg;

typedef struct s_cmd
{
    char        *cmd_name;      
    char        *cmd_path;      
    t_arg       *args;          // lista de argumentos
    char        *infile;        
    char        *outfile;       
    char        *heredoc_delim; 
    int         append_mode;    
    int         has_pipe;       
    int         is_builtin;     
    int         fd_in;          
    int         fd_out;         
    pid_t       pid;
    t_parser	*original_parser; // referencia al parser que lo generó        
    struct s_cmd *next;
}   t_cmd;

typedef struct s_shell
{
	char		**paths; //variables de entorno del sistema
	t_env		*env; //lista de nodos que representa `envp`
	t_lexer		*lexer; //lista de nodos que separa los tokens
	t_parser	*parser; //lista de nodos que separa los comandos
	t_cmd		*cmd_list; //Nueva lista de comandos procesados
	int			exit_status; //entero que representa el estado de salida
}	t_shell;

/*═════════════════════════ [  FUNCTIONS  ] ══════════════════════════════════*/
/*---------------------------- [  lexer  ] -----------------------------------*/
int		is_quotes(char c);
t_token_type	is_symbol(char *str);
int validate_syntax(t_cmd *commands);
int print_error(const char *prefix, const char *msg, int code);

/*--------------------------- [  parser  ] -----------------------------------*/

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diespino <diespino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 13:01:04 by diespino          #+#    #+#             */
/*   Updated: 2025/10/02 12:59:20 by dortega-         ###   ########.fr       */
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
}			t_token_type;

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


/**
* @struct t_arg
* @brief Nodo para una lista de argumentos de un comando.
* Esta estructura contiene un único argumento de comando. 
* Los argumentos para un comando se almacenan en una lista enlazada. 
* Este diseño simplifica el manejo de listas de argumentos de longitud variable durante el análisis (parsing).
* @param arg Una cadena de caracteres (string) asignada dinámicamente para el argumento.
* @param next Un puntero al siguiente argumento en la lista.
*/
typedef struct s_arg
{
    char *value;
    struct s_arg *next;
} t_arg;

/**
 * @struct t_redir
 * @brief Estructura para la información de redirección de comandos.
 * Esta estructura almacena información sobre las redirecciones de entrada/salida
 * identificadas durante el análisis (parsing).
 * @param type Tipo de redirección.
 * @param file Cadena de caracteres (string) asignada dinámicamente para el
 *             nombre del archivo de destino o el delimitador de heredoc.
 * @param next Puntero a la siguiente redirección en la lista.
 */
typedef struct s_redir
{
	t_token_type	type;
	char			*file;
	int             heredoc_fd;
	struct s_redir	*next;
}					t_redir;
/**
 * @struct t_command
 * @brief Estructura para una unidad de comando analizado.
 * Esta estructura representa un único comando identificado por el analizador (parser).
 * @param args  El inicio (cabeza) de una lista enlazada de tipo 't_arg' que contiene
 *              todos los argumentos del comando.
 * @param cmd_argc  El número de argumentos en la lista 'args'.
 * @param redirs  El inicio (cabeza) de una lista enlazada de tipo 't_redir' que contiene
 *                todas las redirecciones del comando.
 * @param is_command  Indicador (bandera/flag) que señala si este nodo de 't_arg' está vacío.
 * @param next  Un puntero al siguiente comando en el flujo de comandos analizados.
*/
typedef struct s_cmd
{
    t_arg			*args;
	size_t			cmd_argc;
	t_redir			*redirs;
	bool			is_command;
	struct s_cmd	*next;
}   t_cmd;
/**
 * @struct t_parse_state
 * @brief Estructura de estado para el proceso de análisis (parsing).
 * Esta estructura mantiene el estado actual durante la fase de análisis,
 * proporcionando un acceso conveniente al comando y a los nodos de redirección
 * que se están construyendo en ese momento.
 * @param cmd_list  Cabeza de la lista completa de comandos que se está construyendo.
 * @param cmd_node  Puntero al nodo de comando actual que se está llenando/poblando.
 * @param redir_node  Puntero al nodo de redirección actual que se está llenando/poblando.
*/
typedef struct s_parse_state
{
	t_cmd	*cmd_list;
	t_cmd	*cmd_node;
	t_redir	*redir_node;
}	t_parse_state;

/*═════════════════════════ [  FUNCTIONS  ] ══════════════════════════════════*/
/*---------------------------- [  lexer  ] -----------------------------------*/
int		is_quotes(char c);
t_token_type	is_symbol(char *str);
int validate_syntax(t_cmd *commands);
int print_error(const char *prefix, const char *msg, int code);

/*--------------------------- [  parser  ] -----------------------------------*/

#endif

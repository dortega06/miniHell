/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dortega- <dortega-@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 10:54:06 by dortega-          #+#    #+#             */
/*   Updated: 2025/12/19 16:23:30 by diespino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
/*═══════════════════════════ [  VAR GLOBAL  ] ═══════════════════════════════*/

extern int	g_signal;

/*═════════════════════════════ [  LIBS  ] ═══════════════════════════════════*/

# include "../libft/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <string.h>
# include <errno.h>
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
# define ERR_CMD "minishell: command not found"
# define ERR_EXP "': not a valid identifier"

# define READLINE_MSG "\033[1;36mminishell\033[34m$> \033[0m"
# define HEREDOC_MSG "\033[1;34m> \033[0m" // @return >

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
	S_BASE,        // señal Base
	S_HEREDOC,     // entra en el heredoc
	S_HEREDOC_END, // finalización del heredoc
	S_SIGINT,      // Ctrl + C
	S_SIGINT_CMD,  // Ctrl + C en medio de una comando
	S_CMD,         // se ejecuta un comando
	S_CANCEL_EXEC, // Ctrl + D en heredoc
	S_SIZE
}			t_signal;

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
	char *var_value;    // valor de la variable
	struct s_env *next; //  siguiente elemento en la lista
}			t_env;

typedef struct s_parser
{
	char *cmd;
	char	**args;             // comando que será ejecutado
	int redir_in;          // redireccionamiento de entrada
	int redir_out;         // redireccionamiento de salida
	struct s_parser *next; //  siguiente elemento en la lista
}			t_parser;

typedef struct s_shell
{
//	char **paths;       // variables de entorno del sistema
	char **cmd_args;    // comando seguido de argumentos
	int count_cmd_args; // cantidad de comando + argumentos
	t_env *env;         // lista de nodos que representa `envp`
	t_lexer *lexer;     // lista de nodos que separa los tokens
	t_parser *parser;   // lista de nodos que separa los comandos
	int exit_status;    // entero que representa el estado de salida
}			t_shell;

/*═════════════════════════ [  FUNCTIONS  ] ══════════════════════════════════*/

/*---------------------------- [  lexer  ] -----------------------------------*/

int		get_type(char *str, int i);
void	ft_lexer(char *input, t_lexer **lexer, int *exit_status);
int		check_syntax(t_lexer *lexer, int *exit_status);
void	lexer_add_token(char *str, t_lexer **lexer, int *i, int size);
int		treat_quotes(char *input, t_lexer **lexer, \
				int *i, int *exit_status);
void    treat_general(char *input, t_lexer **lexer, int *i);
void    treat_special(char *input, t_lexer **lexer, int *i, int type);
void    ft_lexer_var(t_shell *msh);
void	free_token_lst(t_lexer **lexer);

/*--------------------------- [  parser  ] -----------------------------------*/

// PARSER
void    ft_parser(t_parser **parser, t_shell *msh);
void    ft_fill_node(t_parser **cmd_node, int start, int end, t_shell *msh);
void    fill_redir(t_parser **cmd_node, int *start, int end, t_shell *msh);
void    ft_redirect(t_lexer *tmp, t_parser **cmd_node, t_shell *msh);

void	ft_index(t_lexer *lex);
int	ft_count_pipes(t_lexer *lex);
int	get_last(t_lexer *lex, int start);

void	fill_cmd(t_lexer *tmp, t_parser **cmd_node);
int	ft_len_cmd(t_lexer *tmp);
void	free_parser_lst(t_parser **parser);

// HEREDOC
void    ft_heardoc(t_lexer *tmp, t_parser **cmd_node, t_shell *msh);
int     ft_heredoc(char *delimiter, int should_expand, t_shell *msh);
char    *ft_expand_line(char *line, t_shell *msh);
int     ft_has_quotes(char *str);
char    *ft_remove_quotes(char *str);

// REDIRECCIONES
void    ft_redir_in(t_lexer *tmp, t_parser **cmd_node);
void    ft_redir_out(t_lexer *tmp, t_parser **cmd_node);
void    ft_append(t_lexer *tmp, t_parser **cmd_node);
void	process_data(char **data, t_shell *msh);

/*-------------------------- [ treat_quotes ] --------------------------------*/

int	validate_quotes_parser(t_lexer *lex);
char	*strip_quotes(char *str);
char	*process_token_quotes(char *token);
int	is_single_quoted(char *str);
int	is_double_quoted(char *str);

/*-------------------------- [ executer ] ------------------------------------*/

void	ft_executer(t_shell *msh);
void	free_array(char **array);
char	**env_to_array(t_env *env);
char	*get_cmd_path(char *cmd, t_env *env);
char	**split_shell(t_shell *msh, char *str, char c);
char	*trim_quotes(char *str);

/*-------------------------- [ built-ins ] ------------------------------------*/

int		is_builtin(t_shell *msh);
void	ft_builtins(t_shell *msh);
void    ft_env(t_shell *msh);
void	ft_export(t_shell *msh);
void	print_declared_vars(t_shell *msh);
void	ft_unset(t_shell *msh);
int		ft_pwd(void);
void	ft_echo(t_shell *msh);
void	ft_exit_built(t_shell *msh);

/*-------------------------- [ env_utils ] -----------------------------------*/

void	env_init(t_env **env, char **envp);
char	*get_var_name(char *var);
char	*get_var_value(char *var);
void	mshell_lvl(t_env **env);
void	env_add_var(t_env **env, char *name, char *value);
void	free_env_lst(t_env **env);

/*-------------------------- [ print_test_msh ] -------------------------------*/

void	print_array(char **array);
void	print_env(t_env *env);
void	print_tokens(t_lexer *lexer);
void	print_parser(t_parser *parser);

#endif

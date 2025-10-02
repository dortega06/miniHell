/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diespino <diespino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 17:03:46 by diespino          #+#    #+#             */
/*   Updated: 2025/10/02 14:04:30 by diespino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
/*
typedef enum e_token
{
        T_GENERAL,   // 0
        T_CMD,       // 1 comando
        T_PIPE,      // 2 | pipe
        T_REDIR_IN,  // 3 < REDIR_IN
        T_INFILE,    // 4 infile
        T_HEREDOC,   // 5 << HEREDOC
        T_LIMITER,   // 6 (str) para terminar de introducir datos
        T_REDIR_OUT, // 7 > REDIR_OUT
        T_OUTFILE,   // 8 outfile
        T_APPEND,    // 9 >> APPEND
        T_SIZE	     // 10
}*/

// input == tmp == string sin " \t\n\v\f\r" delante y atras
void	ft_lexer(char *input, t_lexer **lexer)
{
	int	i;
	int	type;

	i = 0;
	while (input[i])
	{
		while (ft_isspace(input[i]))
			i++;
		type = get_type(input, i);// clasifica los caracteres
		if (type != T_GENERAL)// si no es una palabra
			treat_special(input, lexer, &i, type);// clasifica metacaracteres
		else if (input[i] == '"' || input[i] == '\'')
		{
			if (!treat_quotes(input, lexer, &i, type))// tokeniza interior de "" y ''
				break ;// si hay error sale del while
		}
		else
			treat_general(input, lexer, &i, type);
	}
	if (!check_syntax(*lexer))
	{
		free_token_lst(lexer);
		return ;
	}
 /*	lexer_cmd(*lexer);
 */
}

// check_syntax_pipe
// [#]lexer->type == T_PIPE --> Primer nodo PIPE
// [#]lexer->type == T_PIPE && !lexer->next --> ultimo nodo PIPE
// [#]lexer->type == T_PIPE && lexer->next->type == T_PIPE --> Dos PIPEs seguidos
// [ ]lexer->type != T_GENERAL && lexer->next->type == T_PIPE --> token != T_GENERAl --> PIEPE
// [ ]lexer->type == T_PIPE && lexer->next->type != T_GENERAL --> PIPE --> token != T_GENERAl
//
// typedef struct s_lexer
// {
//         int             index; //  indice del token
//         char            *data; //  contenido (valor literal)
//         int             type;  //  numero equivalente al token (enum)
//         struct s_lexer  *next; //  siguiente elemento en la lista
// } t_lexer;
//
int	check_syntax_pipe(t_lexer *lexer)
{
	if (!ft_strcmp(lexer->data, "|"))
		return (0);
	while (lexer)
	{
		if (!ft_strcmp(lexer->data, "|") && !lexer->next)
			return (0);
		if (!ft_strcmp(lexer->data, "|") && 
				!ft_strcmp(lexer->next->data, "|"))
			return (0);
		if (lexer->type != T_GENERAL && lexer->next->type == T_PIPE)
			return (0);
		if (lexer->type == T_PIPE && lexer->next->type != T_GENERAL)
			return (0);
		lexer = lexer->next;
	}
	return (1);
}
// check_syntax
int	check_syntax(t_lexer *lexer)
{
	if (!lexer)
		return (0);
	if (!check_syntax_pipe(lexer))
	{
		printf("miniHell: syntax error pipe\n");
		return (0);
	}
/*	while (lexer->next)
	{
		if ((lexer->type == T_REDIR_IN || lexer->type == T_REDIR_OUT ||
			lexer->type == T_HEREDOC || lexer->type == T_APPEND) &&
				lexer->next->type != T_GENERAL)
		{
			printf("miniHell: syntax error near unexpected token\n");
			return (0);
		}
		lexer = lexer->next;
	}*/
	return (1);
}

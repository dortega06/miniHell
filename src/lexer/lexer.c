/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diespino <diespino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 17:03:46 by diespino          #+#    #+#             */
/*   Updated: 2025/10/07 16:32:37 by diespino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void    lexer_cmd(t_lexer *lexer);

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
	lexer_cmd(*lexer);
}

int	check_syntax_pipe(t_lexer *lexer)
{
	if (lexer->type == T_PIPE)
		return (0);
	while (lexer)
	{
		if (lexer->type == T_PIPE && !lexer->next)
			return (0);
		if (!ft_strcmp(lexer->data, "|") && 
				!ft_strcmp(lexer->next->data, "|"))
			return (0);
		if (lexer->type == T_PIPE && 
			(lexer->next->type != T_GENERAL || !lexer->next))
			return (0);
		lexer = lexer->next;
	}
	return (1);
}

int	check_syntax_redir(t_lexer *lexer)
{
	while (lexer)
	{
		if ((lexer->type == T_REDIR_IN || lexer->type == T_REDIR_OUT ||
			lexer->type == T_HEREDOC || lexer->type == T_APPEND) &&
		   		!lexer->next)
		{
			printf("%s 'newline'\n", ERR_TOKEN);
			return (0);
		}
		if ((lexer->type == T_REDIR_IN || lexer->type == T_REDIR_OUT ||
			lexer->type == T_HEREDOC || lexer->type == T_APPEND) &&
				lexer->next->type != T_GENERAL)
		{
			printf("%s '%s'\n", ERR_TOKEN, lexer->next->data);
			return (0);
		}
		lexer = lexer->next;
	}
	return (1);
}

int	check_syntax(t_lexer *lexer)
{
	if (!lexer)
		return (0);
	if (!check_syntax_pipe(lexer))
	{
		printf("%s '|'\n", ERR_TOKEN);
		return (0);
	}
	if (!check_syntax_redir(lexer))
		return (0);
	return (1);
}

/*
 * typedef enum e_token
 * {
 *         T_GENERAL,   // 0
 *       # T_CMD,       // 1 CMD
 *         T_PIPE,      // 2 |
 *         T_REDIR_IN,  // 3 <
 *       # T_INFILE,    // 4 <[INFILE]
 *         T_HEREDOC,   // 5 <<
 *       # T_LIMITER,   // 6 <<[LIMITER]
 *         T_REDIR_OUT, // 7 >
 *       # T_OUTFILE,   // 8 >[OUTFILE]
 *         T_APPEND,    // 9 >>
 *         T_SIZE       // 10
 * }
 * T_CMD	--> COMANDO
 * T_INFILE	--> < [INFILE]
 * T_OUTFILE    --> > [OUTFILE]
 * T_LIMITER	--> >> [LIMITER]
 */
void	lexer_cmd(t_lexer *lexer)
{
	if (lexer->type == T_GENERAL)
		lexer->type = T_CMD;
	while (lexer)
	{
		if (lexer->type == T_PIPE)
			lexer->next->type = T_CMD;
		else if (lexer->type == T_REDIR_IN)
			lexer->next->type = T_INFILE;
		else if (lexer->type == T_REDIR_OUT)
			lexer->next->type = T_OUTFILE;
		else if (lexer->type == T_HEREDOC)
			lexer->next->type = T_LIMITER;
		lexer = lexer->next;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   treat_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diespino <diespino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 15:58:22 by diespino          #+#    #+#             */
/*   Updated: 2025/11/12 11:32:57 by dortega-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// lexer_add_token(string, struct lexer, indice actual, tamano de token, type);
//
// casificar metacaracteres < > << >> |
void	treat_special(char *input, t_lexer **lexer, int *i, int type)
{
	if (type == T_HEREDOC || type == T_APPEND)
	{
		lexer_add_token(input, lexer, i, 2, type);
		(*i) += 2;
	}
	else
	{
		lexer_add_token(input, lexer, i, 1, type);
		(*i)++;
	}
//	(*i)++;
}

// tokeniza palabras dentro de "" y ''
int	treat_quotes(char *input, t_lexer **lexer, int *i, int type)
{
	int     	j;
	char	quote;

	j = (*i) + 1;
	quote = input[*i];
	while (input[j] && input[j] != quote)
		j++;
	if (input[j] == quote)
	{
		lexer_add_token(input, lexer, i, j - (*i) + 1, type);
		(*i) = j + 1;
		return (1);
	}
	else
	{
		lexer_add_token(input, lexer, i, j - (*i) + 1, type);
		printf("miniHell: syntax error open quote\n");
//		exit_status = 2;??
		free_token_lst(lexer);
		return (0);
	}
}
//
// clasifica palabras
void	treat_general(char *input, t_lexer **lexer, int *i, int type)
{
	int	j;

	j = (*i);
	while (input[j] && !ft_isspace(input[j]) && 
			get_type(input, j) == T_GENERAL)
		j++;	
	lexer_add_token(input, lexer, i, j - (*i), type);
	(*i) = j;
}

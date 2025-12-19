/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   treat_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diespino <diespino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 15:58:22 by diespino          #+#    #+#             */
/*   Updated: 2025/12/19 15:13:18 by diespino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	treat_special(char *input, t_lexer **lexer, int *i, int type)
{
	if (type == T_HEREDOC || type == T_APPEND)
	{
		lexer_add_token(input, lexer, i, 2);
		(*i) += 2;
	}
	else
	{
		lexer_add_token(input, lexer, i, 1);
		(*i)++;
	}
}

int	treat_quotes(char *input, t_lexer **lexer, int *i, int *exit_status)
{
	int		j;
	char	quote;

	j = (*i) + 1;
	quote = input[*i];
	while (input[j] && input[j] != quote)
		j++;
	if (input[j] == quote)
	{
		lexer_add_token(input, lexer, i, j - (*i) + 1);
		(*i) = j + 1;
		return (1);
	}
	else
	{
		lexer_add_token(input, lexer, i, j - (*i) + 1);
		printf("miniHell: syntax error open quote\n");
		*exit_status = 2;
		free_token_lst(lexer);
		return (0);
	}
}

void	treat_general(char *input, t_lexer **lexer, int *i)
{
	int	j;
//	int	var;
//	char	quote;

//	var = 0;
	j = (*i);
	while (input[j] && !ft_isspace(input[j]) && !ft_isquote(input[j]) && \
			get_type(input, j) == T_GENERAL)
	{
//		printf("BUCLE 1 %c\n", input[j]);
//		if (input[j] == '=')
///			var = 1;
		j++;
	}
//	printf("VAR: %d\n", var);
/*	if (input[j] == '=')
	{
		printf("ES =\n");
		j++;
	}
	if (ft_isquote(input[j]) && var == 1)
	{
		printf("ENTRA QUOTE\n");
		quote = input[j++];
		while (input[j] && input[j] != quote)
		{
			printf("BUCLE QUOTE %c\n", input[j]);
			j++;
		}
		j++;
	}*/
	while (ft_isspace(input[j]))
		j++;
	lexer_add_token(input, lexer, i, j - (*i));
	(*i) = j;
}

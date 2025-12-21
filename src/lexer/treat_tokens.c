/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   treat_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diespino <diespino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 15:58:22 by diespino          #+#    #+#             */
/*   Updated: 2025/12/21 18:12:25 by dortega-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	treat_special(char *input, t_lexer **lexer, int *i, int type)
{
	int	j;
	int	len;

	len = 0;
	if (type == T_HEREDOC || type == T_APPEND)
	{
		j = (*i) + 2;
		while (ft_isspace(input[j++]))
			len++;
		lexer_add_token(input, lexer, i, (len + 2));
	}
	else
	{
		j = (*i) + 1;
		while (ft_isspace(input[j++]))
			len++;
		lexer_add_token(input, lexer, i, (len + 1));
	}
	(*i) = j - 1;
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

	j = (*i);
	if (ft_isspace(input[j]))
	{
		while (ft_isspace(input[j]))
			j++;
	}
	while (input[j] && !ft_isspace(input[j]) && !ft_isquote(input[j]) && \
			get_type(input, j) == T_GENERAL)
	{
		j++;
	}
	lexer_add_token(input, lexer, i, j - (*i));
	(*i) = j;
}

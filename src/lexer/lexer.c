/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diespino <diespino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 17:03:46 by diespino          #+#    #+#             */
/*   Updated: 2025/11/24 14:10:17 by diespino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int     check_quotes(t_lexer *lexer);

static void	lexer_index(t_lexer *lexer)
{
	int	i;

	i = 0;
	while (lexer)
	{
		lexer->index = i;
		lexer = lexer->next;
		i++;
	}
}

static void	lexer_cmd(t_lexer *lexer)
{
	if (lexer->type == T_GENERAL)
		lexer->type = T_CMD;
	while (lexer)
	{
		if (lexer->type == T_PIPE)
			lexer->next->type = T_CMD;
		else if (lexer->type == T_REDIR_IN)
			lexer->next->type = T_INFILE;
		else if (lexer->type == T_INFILE && 
				lexer->next && lexer->next->type == T_GENERAL)
			lexer->next->type = T_CMD;
		else if (lexer->type == T_REDIR_OUT || lexer->type == T_APPEND)
			lexer->next->type = T_OUTFILE;
		else if (lexer->type == T_HEREDOC)
			lexer->next->type = T_LIMITER;
		lexer = lexer->next;
	}
}

// input == tmp == string sin " \t\n\v\f\r" delante y atras
// Separar en dos funciones
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
		if (type != T_GENERAL)
			treat_special(input, lexer, &i, type); 
		else if (input[i] == '"' || input[i] == '\'')
		{
			if (!treat_quotes(input, lexer, &i, type))
				break ;
		}
		else
			treat_general(input, lexer, &i, type);
	}
	if (!check_syntax(*lexer))// || !check_quotes(*lexer))
		return (free_token_lst(lexer));
	lexer_cmd(*lexer);
//	lexer_var(*lexer);
	lexer_index(*lexer);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diespino <diespino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 13:52:29 by diespino          #+#    #+#             */
/*   Updated: 2025/12/01 15:37:08 by diespino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	check_syntax_pipe(t_lexer *lexer)
{
	if (lexer->type == T_PIPE)
		return (0);
	while (lexer)
	{
		if (lexer->type == T_PIPE && !lexer->next)
			return (0);
		if (!ft_strcmp(lexer->data, "|") && \
				!ft_strcmp(lexer->next->data, "|"))
			return (0);
		if (lexer->type == T_PIPE && \
			(lexer->next->type != T_GENERAL || !lexer->next))
			return (0);
		lexer = lexer->next;
	}
	return (1);
}

static int	check_syntax_redir(t_lexer *lexer, int *exit_status)
{
	while (lexer)
	{
		if ((lexer->type == T_REDIR_IN || lexer->type == T_REDIR_OUT || \
			lexer->type == T_HEREDOC || lexer->type == T_APPEND) && \
				!lexer->next)
		{
			printf("%s `newline'\n", ERR_TOKEN);
			*exit_status = 2;
			return (0);
		}
		if ((lexer->type == T_REDIR_IN || lexer->type == T_REDIR_OUT || \
			lexer->type == T_HEREDOC || lexer->type == T_APPEND) && \
				lexer->next->type != T_GENERAL)
		{
			printf("%s `%s'\n", ERR_TOKEN, lexer->next->data);
			*exit_status = 2;
			return (0);
		}
		lexer = lexer->next;
	}
	return (1);
}

int	check_syntax(t_lexer *lexer, int *exit_status)
{
	if (!lexer)
		return (0);
	if (!check_syntax_pipe(lexer))
	{
		return (printf("%s `|'\n", ERR_TOKEN), 0);
		*exit_status = 2;
	}
	if (!check_syntax_redir(lexer, exit_status))
		return (0);
	return (1);
}

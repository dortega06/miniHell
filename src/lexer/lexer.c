/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diespino <diespino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 17:03:46 by diespino          #+#    #+#             */
/*   Updated: 2025/12/03 14:24:51 by diespino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
		else if (lexer->type == T_INFILE && \
				lexer->next && lexer->next->type == T_GENERAL)
			lexer->next->type = T_CMD;
		else if (lexer->type == T_REDIR_OUT || lexer->type == T_APPEND)
			lexer->next->type = T_OUTFILE;
		else if (lexer->type == T_HEREDOC)
			lexer->next->type = T_LIMITER;
		lexer = lexer->next;
	}
}

void	ft_lexer(char *input, t_lexer **lexer, int *exit_status)
{
	int	i;
	int	type;

	i = 0;
	while (input[i])
	{
		while (ft_isspace(input[i]))
			i++;
		type = get_type(input, i);
		if (type != T_GENERAL)
			treat_special(input, lexer, &i, type);
		else if (input[i] == '"' || input[i] == '\'')
		{
			if (!treat_quotes(input, lexer, &i, exit_status))
				break ;
		}
		else
			treat_general(input, lexer, &i);
	}
	if (!check_syntax(*lexer, exit_status))
		return (free_token_lst(lexer));
	lexer_cmd(*lexer);
	lexer_index(*lexer);
}

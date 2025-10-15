/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dortega- <dortega-@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 18:52:59 by dortega-          #+#    #+#             */
/*   Updated: 2025/10/15 19:08:22 by dortega-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_lexer	*find_start_node(t_lexer *lex, int start)
{
	t_lexer	*tmp;

	tmp = lex;
	while (tmp && tmp->index != start)
		tmp = tmp->next;
	return (tmp);
}

void	process_redirections(t_lexer *start_node, t_parser **cmd_node, int *start, int end)
{
	t_lexer	*tmp;
	int		aux;

	tmp = start_node;
	aux = *start;
	while(tmp && aux <= end)
	{
		if (tmp->type == T_REDIR_IN || tmp->type == T_REDIR_OUT
			|| tmp->type == T_APPEND || tmp->type == T_HEREDOC)
		{
			if (tmp->index == *start)
				*start += 2;
			ft_redirect(tmp, cmd_node);
		}
		tmp = tmp->next;
		aux++;
	}
}

void	fill_redir(t_lexer *lex, t_parser **cmd_node, int *start, int end)
{
	t_lexer	*start_node;

	start_node = find_start_node(lex, *start);
	process_redirections(start_node, cmd_node, start, end);
}

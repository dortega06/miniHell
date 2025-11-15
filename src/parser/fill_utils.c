/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dortega- <dortega-@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 18:52:59 by dortega-          #+#    #+#             */
/*   Updated: 2025/11/15 14:29:56 by dortega-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	fill_redir(t_lexer *lex, t_parser **cmd_node, int *start, int end)
{
	t_lexer	*tmp;
	int	aux;

	tmp = lex;
	while (tmp && tmp->index != *start)
		tmp = tmp->next;
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

void ft_memfree(void *ptr)
{
	if (!ptr)
		return ;
	free(ptr);
	ptr = NULL;
}

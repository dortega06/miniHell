/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dortega- <dortega-@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 20:56:40 by dortega-          #+#    #+#             */
/*   Updated: 2025/09/20 17:41:44 by dortega-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*Asigna índices a cada nodo en una lista enlazada de tokens.*/
void	ft_index(t_lexer *lex)
{
	t_lexer	*tmp;
	int		i;

	tmp = lex;
	i = 0;
	while (tmp)
	{
		tmp->index = i;
		tmp = tmp->next;
		i++;
	}
}

int	ft_count_pipes(t_lexer *lex)
{
	t_lexer	*tmp;
	int		i;

	tmp = lex;
	i = 0;
	while (tmp)
	{
		if (tmp->type == T_PIPE)
			i++;
		tmp = tmp->next;
	}
	return (i);
}

int	get_last(t_lexer *lex, int start)
{
	t_lexer	*tmp;
	int		last_ind;
	
	last_ind = -1;
	tmp = lex;
	while (tmp && tmp->next)
	{
		if (tmp->type == T_PIPE && tmp->idex > start)
			return (tmp->index - 1);
		tmp = tmp->next;
	}
	last_ind = tmp->next;
	return (last_ind);
}

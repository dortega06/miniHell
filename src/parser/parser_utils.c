/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dortega- <dortega-@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 13:25:08 by dortega-          #+#    #+#             */
/*   Updated: 2025/10/28 15:40:11 by dortega-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_parser_lst(t_parser **parser)
{
	t_parser	*tmp;
	int			i;
	while (*parser)
	{
		tmp = (*parser)->next;
		if ((*parser)->args)
		{
			i = 0;
			while ((*parser)->args[i])
			{
				free((*parser)->args[i]);
				i++;
			}
			free((*parser)->args);
		}
		ft_memfree((*parser)->cmd);
		ft_memfree(*parser);
		*parser = tmp;
	}
	*parser = NULL;
}

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
	int		last;

	last = -1;
	tmp = lex;
	while (tmp && tmp->next)
	{
		if (tmp->type == T_PIPE && tmp->index > start)
			return (tmp->index - 1);
		tmp = tmp->next;
	}
	last = tmp->index;
	return (last);
}

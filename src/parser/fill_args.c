/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_args.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dortega- <dortega-@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/06 13:45:04 by dortega-          #+#    #+#             */
/*   Updated: 2025/12/08 14:09:17 by dortega-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_count_args(t_lexer *tmp)
{
	int	count;

	count = 0;
	while (tmp && (tmp->type == T_CMD || tmp->type == T_GENERAL))
	{
		count++;
		tmp = tmp->next;
	}
	return (count);
}

void	fill_args(t_lexer *tmp, t_parser **cmd_node)
{
	int	count;
	int	i;

	i = 0;
	count = ft_count_args(tmp);
	(*cmd_node)->args = ft_calloc(count + 1, sizeof(char *));
	if (!(*cmd_node)->args)
		return ;
	while (tmp && (tmp->type == T_CMD || tmp->type == T_GENERAL))
	{
		(*cmd_node)->args[i] = ft_strdup(tmp->data);
		i++;
		tmp = tmp->next;
	}
	(*cmd_node)->args[i] = NULL;
}

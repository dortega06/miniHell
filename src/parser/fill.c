/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dortega- <dortega-@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 18:49:25 by dortega-          #+#    #+#             */
/*   Updated: 2025/10/02 20:42:45 by dortega-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	fill_args(t_lexer *tmp, t_cmd **cmd_node)
{
    while (tmp && tmp->type == T_CMD)
    {
        t_arg *new_arg = malloc(sizeof(t_arg));
        if (!new_arg)
            return ; // Manejar error de memoria
        new_arg->value = ft_strdup(tmp->data);
        new_arg->next = NULL;
        if (!(*cmd_node)->args)
            (*cmd_node)->args = new_arg;
        else
        {
            t_arg *last = (*cmd_node)->args;
            while (last->next)
                last = last->next;
            last->next = new_arg;
        }
        (*cmd_node)->cmd_argc++;
        tmp = tmp->next;
    }
}

void	ft_fill_cmd_node(t_lexer *lex, t_cmd **cmd_node, int start, int end)
{
    t_lexer	*tmp = lex;

    (*cmd_node)->args = NULL;
    (*cmd_node)->redirs = NULL;
    (*cmd_node)->cmd_argc = 0;
    (*cmd_node)->is_command = false;

    fill_redir(lex, cmd_node, &start, end);

    while (tmp && tmp->index != start)
        tmp = tmp->next;

    fill_args(tmp, cmd_node);
}

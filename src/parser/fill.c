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
static t_redir	*create_redir_node(t_lexer *tmp)
{
    t_redir *new_redir;

    new_redir = malloc(sizeof(t_redir));
    if (!new_redir)
        return (NULL);
    new_redir->type = tmp->type;
    new_redir->file = ft_strdup(tmp->next->data);
    new_redir->heredoc_fd = -1;
    new_redir->next = NULL;
    return (new_redir);
}

static void	add_redir_to_list(t_cmd **cmd_node, t_redir *new_redir)
{
    t_redir *last;

    if (!(*cmd_node)->redirs)
        (*cmd_node)->redirs = new_redir;
    else
    {
        last = (*cmd_node)->redirs;
        while (last->next)
            last = last->next;
        last->next = new_redir;
    }
}

static void	fill_redir(t_lexer *lex, t_cmd **cmd_node, int *start, int end)
{
    t_lexer	*tmp = lex;
    int		aux = *start;
    t_redir	*new_redir;

    while (tmp && tmp->index != *start)
        tmp = tmp->next;
    while (tmp && aux <= end)
    {
        if (tmp->type == T_REDIR_IN || tmp->type == T_REDIR_OUT
            || tmp->type == T_APPEND || tmp->type == T_HEREDOC)
        {
            new_redir = create_redir_node(tmp);
            if (new_redir)
                add_redir_to_list(cmd_node, new_redir);
            if (tmp->index == *start)
                *start += 2;
        }
        tmp = tmp->next;
        aux++;
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


#include "../../includes/minishell.h"
#include <stdio.h>
#include <stdlib.h>

// Función auxiliar para crear nodos lexer
t_lexer *create_lexer_node(char *data, int type, int index)
{
    t_lexer *node = malloc(sizeof(t_lexer));
    node->data = ft_strdup(data);
    node->type = type;
    node->index = index;
    node->next = NULL;
    return node;
}

// Función auxiliar para imprimir los argumentos
void print_args(t_arg *args)
{
    printf("Args: ");
    while (args)
    {
        printf("[%s] ", args->value);
        args = args->next;
    }
    printf("\n");
}

// Función auxiliar para imprimir los redirs
void print_redirs(t_redir *redirs)
{
    printf("Redirs: ");
    while (redirs)
    {
        printf("[type:%d file:%s] ", redirs->type, redirs->file);
        redirs = redirs->next;
    }
    printf("\n");
}

int main(void)
{
    // Simula: cat archivo.txt > salida.txt
    t_lexer *l1 = create_lexer_node("cat", T_CMD, 0);
    t_lexer *l2 = create_lexer_node("archivo.txt", T_CMD, 1);
    t_lexer *l3 = create_lexer_node(">", T_REDIR_OUT, 2);
    t_lexer *l4 = create_lexer_node("salida.txt", T_CMD, 3);

    l1->next = l2;
    l2->next = l3;
    l3->next = l4;

    t_cmd *cmd = malloc(sizeof(t_cmd));
    ft_fill_cmd_node(l1, &cmd, 0, 3);

    print_args(cmd->args);
    print_redirs(cmd->redirs);

    // Liberar memoria aquí si lo deseas

    return 0;
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dortega- <dortega-@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 19:03:35 by dortega-          #+#    #+#             */
/*   Updated: 2025/10/15 19:04:32 by dortega-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// Construye una lista t_lexer simple para test
t_lexer *lexer_new(int type, char *data, int index) {
    t_lexer *node = malloc(sizeof(t_lexer));
    node->type = type;
    node->data = data;
    node->index = index;
    node->next = NULL;
    return node;
}

void lexer_add_back(t_lexer **lst, t_lexer *new) {
    t_lexer *tmp = *lst;
    if (!tmp) {
        *lst = new;
        return;
    }
    while (tmp->next)
        tmp = tmp->next;
    tmp->next = new;
}

// MAIN DE PRUEBA
int main(void)
{
    // Creamos una lista: echo hola > out.txt
    t_lexer *lex = NULL;
    lexer_add_back(&lex, lexer_new(T_CMD, "echo", 0));
    lexer_add_back(&lex, lexer_new(T_CMD, "hola", 1));
    lexer_add_back(&lex, lexer_new(T_REDIR_OUT, ">", 2));
    lexer_add_back(&lex, lexer_new(T_CMD, "out.txt", 3));

    t_parser *cmd_node = calloc(1, sizeof(t_parser));
    int start = 0;
    int end = 3;

    ft_fill_node(lex, &cmd_node, start, end); // Inicializa redirecciones

    // Procesa redirecciones (simula funciones de fill_utils.c)
    fill_redir(lex, &cmd_node, &start, end);

    // Procesa comandos
    t_lexer *tmp = lex;
    while (tmp && tmp->type == T_CMD)
        tmp = tmp->next;
    fill_cmd(lex, &cmd_node);

    // Muestra resultados
    printf("cmd: %s\n", cmd_node->cmd);
    printf("redir_in: %d\n", cmd_node->redir_in);
    printf("redir_out: %d\n", cmd_node->redir_out);

    // Limpieza
    free(cmd_node->cmd);
    free(cmd_node);
    t_lexer *aux;
    while (lex) {
        aux = lex->next;
        free(lex);
        lex = aux;
    }
    return 0;
}

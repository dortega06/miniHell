/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dortega- <dortega-@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 15:45:54 by dortega-          #+#    #+#             */
/*   Updated: 2025/09/15 16:10:57 by dortega-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int print_error(const char *prefix, const char *msg, int code)
{
    (void)prefix;
    fprintf(stderr, "%s", msg);
    return code;
}

t_token *new_token(t_token_type type, char *value) {
    t_token *tok = malloc(sizeof(t_token));
    tok->type = type;
    tok->value = value;
    tok->position = 0;
    tok->next = NULL;
    return tok;
}

t_redir *new_redir(int type, char *file) {
    t_redir *r = malloc(sizeof(t_redir));
    r->type = type;
    r->fd_in = -1;
    r->ft_out = -1;
    r->file = file;
    r->next = NULL;
    return r;
}

t_cmd *new_cmd(t_token *tokens, t_redir *redir) {
    t_cmd *c = malloc(sizeof(t_cmd));
    c->tokens = tokens;
    c->redirects = redir;
    c->next = NULL;
    return c;
}

// --- MAIN: probamos casos ---
int main(void) {
    // Caso válido: ls -l
    t_cmd *cmd1 = new_cmd(new_token(WORD, "ls"), NULL);
    cmd1->tokens->next = new_token(WORD, "-l");
    printf("Test 1 (ls -l): %d\n", validate_syntax(cmd1));

    // Caso válido: echo hola > out.txt
    t_cmd *cmd2 = new_cmd(new_token(WORD, "echo"), new_redir(REDIR_OUT, "out.txt"));
    cmd2->tokens->next = new_token(WORD, "hola");
    printf("Test 2 (echo hola > out.txt): %d\n", validate_syntax(cmd2));

    // Caso inválido: cat <
    t_cmd *cmd3 = new_cmd(new_token(WORD, "cat"), new_redir(REDIR_IN, NULL));
    printf("Test 3 (cat <): %d\n", validate_syntax(cmd3));

    // Caso inválido: | ls
    t_cmd *cmd4 = new_cmd(NULL, NULL);
    cmd4->next = new_cmd(new_token(WORD, "ls"), NULL);
    printf("Test 4 (| ls): %d\n", validate_syntax(cmd4));

    // Caso válido: ls | wc -l
    t_cmd *cmd5a = new_cmd(new_token(WORD, "ls"), NULL);
    t_cmd *cmd5b = new_cmd(new_token(WORD, "wc"), NULL);
    cmd5b->tokens->next = new_token(WORD, "-l");
    cmd5a->next = cmd5b;
    printf("Test 5 (ls | wc -l): %d\n", validate_syntax(cmd5a));

    // Caso inválido: token raro (ERROR)
    t_cmd *cmd6 = new_cmd(new_token(WORD, "ls"), NULL);
    cmd6->tokens->next = new_token(ERROR, "@"); // token inválido
    printf("Test 6 (ls @ file): %d\n", validate_syntax(cmd6));

    return 0;
}

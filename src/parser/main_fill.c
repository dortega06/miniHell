/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_fill.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dortega- <dortega-@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/22 19:26:15 by dortega-          #+#    #+#             */
/*   Updated: 2025/11/29 13:58:45 by dortega-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	g_signal = S_BASE;

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "minishell.h"

/* ════════════════════════ UTILS PARA EL TEST ════════════════════════ */

void print_lexer(t_lexer *lexer)
{
    static const char *type_names[] = {
        "T_GENERAL",
        "T_CMD",
        "T_PIPE",
        "T_REDIR_IN",
        "T_INFILE",
        "T_HEREDOC",
        "T_LIMITER",
        "T_REDIR_OUT",
        "T_OUTFILE",
        "T_APPEND"
    };

    printf("\n=== LEXER OUTPUT ===\n");
    while (lexer)
    {
        printf("Index: %-2d | Type: %-12s | Data: [%s]\n",
            lexer->index, type_names[lexer->type], lexer->data);
        lexer = lexer->next;
    }
    printf("====================\n\n");
}

void print_parser(t_parser *parser, t_lexer *lexer)
{
    int node = 0;

    printf("\n=== PARSER OUTPUT ===\n");
    while (parser)
    {
        printf("Node %d:\n", node);

        printf("  Command: [%s]\n",
            parser->cmd ? parser->cmd : "(null)");    
		printf("  redir_in:  %d\n", parser->redir_in);
        printf("  redir_out: %d\n", parser->redir_out);
        printf("\n");
        /* Detectamos si el input es heredoc mirando el lexer */
        int is_heredoc = 0;
        char *limiter = NULL;

        t_lexer *tmp = lexer;
        while (tmp)
        {
            if (tmp->type == T_HEREDOC)
            {
                is_heredoc = 1;
                if (tmp->next && tmp->next->type == T_LIMITER)
                    limiter = tmp->next->data;
                break;
            }
            tmp = tmp->next;
        }

        /* Mostramos IN según si es heredoc o < infile */
        if (is_heredoc)
        {
            printf("  Redir IN (HEREDOC): FD=%d | Limiter=[%s]\n",
                parser->redir_in,
                limiter ? limiter : "(null)");
        }
        else
        {
            printf("  Redir IN:  %d %s\n",
                parser->redir_in,
                parser->redir_in == STDIN_FILENO ? "(STDIN)" : "(file)");
        }

        printf("  Redir OUT: %d %s\n",
            parser->redir_out,
            parser->redir_out == STDOUT_FILENO ? "(STDOUT)" : "(file)");

        printf("\n");
        parser = parser->next;
        node++;
    }
    printf("=====================\n\n");
}

void free_parser(t_parser **parser)
{
    t_parser *tmp;
    t_parser *next;

    if (!parser || !*parser)
        return;
    tmp = *parser;
    while (tmp)
    {
        next = tmp->next;
        if (tmp->cmd)
            free(tmp->cmd);
        if (tmp->redir_in > 2)
            close(tmp->redir_in);
        if (tmp->redir_out > 2)
            close(tmp->redir_out);
        free(tmp);
        tmp = next;
    }
    *parser = NULL;
}

/* ═══════════════════════ TEST RUNNER ═══════════════════════ */

void test_input(char *input)
{
    t_lexer *lexer = NULL;
    t_parser *parser = NULL;

    printf("\n╔════════════════════════════════════════════════════════════╗\n");
    printf("║ Testing: %-49s ║\n", input);
    printf("╚════════════════════════════════════════════════════════════╝\n");

    ft_lexer(input, &lexer);
    if (!lexer)
    {
        printf("❌ Lexer failed\n");
        return;
    }

    print_lexer(lexer);

    ft_parser(&parser, lexer);

    if (!parser)
    {
        printf("❌ Parser failed\n");
        free_token_lst(&lexer);
        return;
    }

    print_parser(parser, lexer);
    free_parser(&parser);
    free_token_lst(&lexer);
}

/* ════════════════════════ MAIN  ════════════════════════ */

int main(void)
{
    printf("\n\nMINISHELL PARSER TEST SUITE\n\n");

    test_input("cat file.txt | grep hello");
    test_input("ls -la");
    test_input("echo \"hola\"");
    test_input("cat < input.txt");
    test_input("echo hello > output.txt");
    test_input("echo world >> output.txt");
    test_input("cat file.txt | grep hello | wc -l");
    test_input("cat < input.txt | grep test > output.txt");
    test_input("ls -la | grep .c >> results.txt");
    test_input("cat < input.txt > output.txt");

    /* HEREDOC TESTS */
    test_input("cat << EOF");
    test_input("cat << 'EOF'");
    test_input("cat <<EOF | grep hola");
    test_input("grep foo <<LIMIT");
    test_input("cat << EOF << FIN");

    /* QUOTES TESTS */
    test_input("echo \"hola mundo\"");
    test_input("echo hola mundo\"");
    test_input("echo \"hola mundo");

    return (0);
}


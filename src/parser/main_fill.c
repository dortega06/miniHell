/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_fill.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dortega- <dortega-@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/22 19:26:15 by dortega-          #+#    #+#             */
/*   Updated: 2025/11/22 19:26:34 by dortega-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int g_signal = S_BASE;

/*
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
}*/

void print_lexer(t_lexer *lexer)
{
	t_lexer *tmp;
	const char *type_names[] = {
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
	tmp = lexer;
	while (tmp)
	{
		printf("Index: %d | Type: %-12s | Data: [%s]\n",
			tmp->index, type_names[tmp->type], tmp->data);
		tmp = tmp->next;
	}
	printf("====================\n\n");
}

void print_parser(t_parser *parser)
{
	t_parser *tmp;
	int node_num;

	printf("\n=== PARSER OUTPUT ===\n");
	tmp = parser;
	node_num = 0;
	while (tmp)
	{
		printf("Node %d:\n", node_num);
		printf("  Command: [%s]\n", tmp->cmd ? tmp->cmd : "(null)");
		printf("  Redir IN:  %d %s\n", tmp->redir_in,
			tmp->redir_in == STDIN_FILENO ? "(STDIN)" : "(file/pipe)");
		printf("  Redir OUT: %d %s\n", tmp->redir_out,
			tmp->redir_out == STDOUT_FILENO ? "(STDOUT)" : "(file/pipe)");
		printf("\n");
		tmp = tmp->next;
		node_num++;
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

void test_input(char *input)
{
	t_lexer *lexer;
	t_parser *parser;

	printf("\n╔════════════════════════════════════════════════════════════╗\n");
	printf("║ Testing: %-49s ║\n", input);
	printf("╚════════════════════════════════════════════════════════════╝\n");

	lexer = NULL;
	parser = NULL;

	ft_lexer(input, &lexer);
	
	if (!lexer)
	{
		printf("❌ Lexer failed to parse input\n");
		return;
	}

	print_lexer(lexer);


	ft_parser(&parser, lexer);
	
	if (parser)
	{
		print_parser(parser);
		free_parser(&parser);
	}
	else
	{
		printf("❌ Parser failed\n");
	}

	free_token_lst(&lexer);
}

int main(void)
{
	printf("\n");
	printf("███╗   ███╗██╗███╗   ██╗██╗███████╗██╗  ██╗███████╗██╗     ██╗\n");
	printf("████╗ ████║██║████╗  ██║██║██╔════╝██║  ██║██╔════╝██║     ██║\n");
	printf("██╔████╔██║██║██╔██╗ ██║██║███████╗███████║█████╗  ██║     ██║\n");
	printf("██║╚██╔╝██║██║██║╚██╗██║██║╚════██║██╔══██║██╔══╝  ██║     ██║\n");
	printf("██║ ╚═╝ ██║██║██║ ╚████║██║███████║██║  ██║███████╗███████╗███████╗\n");
	printf("╚═╝     ╚═╝╚═╝╚═╝  ╚═══╝╚═╝╚══════╝╚═╝  ╚═╝╚══════╝╚══════╝╚══════╝\n");
	printf("\n                    PARSER TEST SUITE\n\n");

	// Test 1: Simple command
	test_input("ls -la");

	// Test 2: Command with pipe
	test_input("cat file.txt | grep hello");

	// Test 3: Input redirection
	test_input("cat < input.txt");

	// Test 4: Output redirection
	test_input("echo hello > output.txt");

	// Test 5: Append redirection
	test_input("echo world >> output.txt");

	// Test 6: Multiple pipes
	test_input("cat file.txt | grep hello | wc -l");

	// Test 7: Complex with multiple redirections
	test_input("cat < input.txt | grep test > output.txt");

	// Test 8: Append with pipe
	test_input("ls -la | grep .c >> results.txt");

	// Test 9: Multiple redirections on same command
	test_input("cat < input.txt > output.txt");

	// Test 10: Heredoc (commented out as it requires user input)
//	test_input("cat << EOF");

	test_input("echo \"hola mundo\"");

	test_input("echo hola mundo\"");

	test_input("echo \"hola mundo");

	// Test 33: Comillas vacías simples
    test_input("echo ''");

    // Test 34: Comillas vacías múltiples
    test_input("echo '' '' ''");
	test_input("echo 'hello \"world");
	printf("\n✅ All tests completed!\n\n");
	printf("Note: Heredoc tests are commented out as they require interactive input.\n");
	printf("To test heredoc manually, uncomment the test and provide the delimiter.\n\n");

	return (0);
}

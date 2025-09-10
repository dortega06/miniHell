/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_parser.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dortega- <dortega-@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 14:18:08 by dortega-          #+#    #+#             */
/*   Updated: 2025/09/10 14:25:55 by dortega-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_parser *create_parser(t_token *token) //funcion que me construye de la estructura t_parser
{
	t_parser	*parser;

	if (!token)
		return (NULL);
	parser = malloc(sizeof(t_parser));
	if (!parser)
		return (NULL);
	parser->token = token; //asigna la lista de tokens
	parser->current_node = token; //empieza desde el primer token
	parser->has_error = false;
	parser->error_message = NULL;
	return (parser);
}


/*
#include <string.h>

int	main(void)
{
	printf("=== PROBANDO create_parser ===\n\n");

	// Crear algunos tokens de ejemplo
	t_token test_tokens[] = {
		{WORD, "ls", 0},
		{WORD, "-la", 3},
		{PIPE, "|", 7}
	};
	int token_count = 3;

	printf("Tokens de prueba:\n");
	int i = 0;
	while (i < token_count)
	{
		printf("  [%d] tipo=%d, valor='%s', pos=%d\n",
			i, test_tokens[i].type, test_tokens[i].value, test_tokens[i].position);
		i++;
	}
	printf("\n");

	// PRUEBA 1: Crear parser normal
	printf("--- PRUEBA 1: Crear parser normal ---\n");
	t_parser *parser = create_parser(test_tokens, token_count);

	if (parser)
	{
		printf("✅ Parser creado exitosamente\n");
		printf("   - tokens: %p\n", (void *)parser->tokens);
		printf("   - current: %d\n", parser->current);
		printf("   - token_count: %d\n", parser->token_count);
		printf("   - has_error: %s\n", parser->has_error ? "true" : "false");
		free(parser);
	}
	else
	{
		printf("❌ Error al crear parser\n");
	}

	// PRUEBA 2: Crear parser con tokens NULL
	printf("\n--- PRUEBA 2: Tokens NULL ---\n");
	t_parser *parser2 = create_parser(NULL, 3);
	if (!parser2)
		printf("✅ Correctamente rechazó tokens NULL\n");
	else
		printf("❌ No debería haber creado parser con tokens NULL\n");

	// PRUEBA 3: Crear parser con count 0
	printf("\n--- PRUEBA 3: Token count 0 ---\n");
	t_parser *parser3 = create_parser(test_tokens, 0);
	if (!parser3)
		printf("✅ Correctamente rechazó token_count 0\n");
	else
		printf("❌ No debería haber creado parser con count 0\n");

	return (0);
}*/

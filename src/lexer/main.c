/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diespino <diespino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 16:02:11 by diespino          #+#    #+#             */
/*   Updated: 2025/10/08 13:56:59 by diespino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 * typedef enum e_token
 * {
 *         T_GENERAL,   // 0
 *         T_CMD,       // 1 CMD
 *         T_PIPE,      // 2 |
 *         T_REDIR_IN,  // 3 <
 *         T_INFILE,    // 4 <[INFILE]
 *         T_HEREDOC,   // 5 <<
 *         T_LIMITER,   // 6 <<[LIMITER]
 *         T_REDIR_OUT, // 7 >
 *         T_OUTFILE,   // 8 >[OUTFILE]
 *         T_APPEND,    // 9 >>
 *         T_SIZE       // 10
 * }
 */
void	print_tokens(t_lexer *lexer)
{
//	printf("\n");
	while (lexer != NULL)
	{
		if (lexer->type == T_GENERAL)
			printf("T_GENERAL   | type=%d | %s\n", lexer->type, lexer->data);
		else if (lexer->type == T_CMD)
			printf("T_CMD       | type=%d | %s\n", lexer->type, lexer->data);
		else if (lexer->type == T_PIPE)
			printf("T_PIPE      | type=%d | %s\n", lexer->type, lexer->data);
		else if (lexer->type == T_REDIR_IN)
			printf("T_REDIR_IN  | type=%d | %s\n", lexer->type, lexer->data);
		else if (lexer->type == T_INFILE)
			printf("T_INFILE    | type=%d | %s\n", lexer->type, lexer->data);
		else if (lexer->type == T_HEREDOC)
			printf("T_HEREDOC   | type=%d | %s\n", lexer->type, lexer->data);
		else if (lexer->type == T_LIMITER)
			printf("T_LIMITER   | type=%d | %s\n", lexer->type, lexer->data);
		else if (lexer->type == T_REDIR_OUT)
			printf("T_REDIR_OUT | type=%d | %s\n", lexer->type, lexer->data);
		else if (lexer->type == T_OUTFILE)
			printf("T_OUTFILE   | type=%d | %s\n", lexer->type, lexer->data);
		else if (lexer->type == T_APPEND)
			printf("T_APPEND    | type=%d | %s\n", lexer->type, lexer->data);
		else
			printf("type=%d | %s\n", lexer->type, lexer->data);
		lexer = lexer->next;
	}
//	printf("\n");
}

int	main(int argc, char **argv)
{
	char	*input;
//	char	*tmp;
	t_lexer	*lexer;

	if (argc != 1 || argv[1])
		return (EXIT_FAILURE);
	while (1)
	{
		lexer = NULL;
		input = readline(" minisHell$> ");
		if (!input)
			break ;
//		printf("|%s|\n", input);
		ft_lexer(ft_strtrim(input, " \t\n\v\f\r"), &lexer);
		print_tokens(lexer);
		free(input);
		free_token_lst(&lexer);
	}
	return (0);
}
//
//static void	free_minishell(char **)

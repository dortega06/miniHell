/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diespino <diespino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 16:02:11 by diespino          #+#    #+#             */
/*   Updated: 2025/10/02 15:07:35 by diespino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	print_tokens(t_lexer *lexer)
{
	while (lexer != NULL)
	{
		printf("type=%d | %s\n", lexer->type, lexer->data);
		lexer = lexer->next;
	}
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
//		tmp = ft_strtrim(input, " \t\n\v\f\r");
		ft_lexer(ft_strtrim(input, " \t\n\v\f\r"), &lexer);
		print_tokens(lexer);
//		free(tmp);
		free(input);
		free_token_lst(&lexer);
	}
	return (0);
}
//
//static void	free_minishell(char **)

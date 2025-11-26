/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diespino <diespino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 16:02:11 by diespino          #+#    #+#             */
/*   Updated: 2025/11/22 13:28:02 by diespino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	main(int argc, char **argv)
{
	char		*input;
	t_shell		msh;

	if (argc != 1 || argv[1])
		return (EXIT_FAILURE);
	while (1)
	{
		input = readline(" minisHell$> ");
		if (!input)
			break ;
		ft_lexer(ft_strtrim(input, " \t\n\v\f\r"), &msh.lexer);
//		ft_exec();
		free_token_lst(&msh.lexer);
		free(input);
	}
	return (0);
}


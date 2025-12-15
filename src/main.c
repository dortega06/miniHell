/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diespino <diespino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 16:02:11 by diespino          #+#    #+#             */
/*   Updated: 2025/12/15 15:34:04 by diespino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	g_signal = S_BASE;

void	pre_exec(char *tmp, t_shell *msh)
{
	ft_lexer(tmp, &msh->lexer, &msh->exit_status);
	ft_lexer_var(msh);
	ft_parser(&msh->parser, msh);
}

void	free_mshell(char *input, char *tmp, t_shell *msh)
{
	free(input);
	free(tmp);
	free_token_lst(&msh->lexer);
	free_parser_lst(&msh->parser);
}

void	ft_minishell(t_shell *msh, char **envp)
{
	char	*input;
	char	*tmp;

	env_init(&msh->env, envp);
//	print_env(msh->env);
	msh->exit_status = 1;// NO VA AQUI, SOLO ES UN TEST
	while (1)
	{
//		if S_SIGINIT;
//		msh->exit_status = 1;
		input = readline(" minisHell$> ");
		if (!input)
			break ;
		tmp = ft_strtrim(input, " \t\n\v\f\r");
		if (tmp && tmp[0] != '\0')
			add_history(tmp);
		if (!ft_strcmp(tmp, "exit"))
		{
			free(tmp);
			free(input);
			break ;
		}
		pre_exec(tmp, msh);

		print_tokens(msh->lexer);
		print_parser(msh->parser);
		
		ft_executer(msh);
		free_mshell(input, tmp, msh);
	}
	free_env_lst(&msh->env);
	rl_clear_history();
}

int	main(int argc, char **argv, char **envp)
{
	t_shell	msh;

	if (argc != 1 || argv[1])
		return (EXIT_FAILURE);
//	signal_init();
	ft_memset(&msh, 0, sizeof(t_shell));
	ft_minishell(&msh, envp);
	return (EXIT_SUCCESS);
}

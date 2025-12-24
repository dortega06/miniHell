/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dortega- <dortega-@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 10:53:49 by dortega-          #+#    #+#             */
/*   Updated: 2025/12/21 18:09:05 by dortega-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

extern int	g_signal;

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
	t_parser	*parser_backup;
	env_init(&msh->env, envp);
	while (1)
	{
		setup_signals(S_BASE);
		g_signal = S_BASE;
		msh->count_heredoc = 0;
		input = readline("🔥mini\033[31;1mHell\033[0m$> ");
		if (g_signal == S_SIGINT_CMD)
		{
			msh->exit_status = 130;
			g_signal = S_BASE;
		}
		if (! input)
		{
			break ;
		}
		tmp = ft_strtrim(input, " \t\n\v\f\r");
		if (! tmp || tmp[0] == '\0')
		{
			free_mshell(input, tmp, msh);
			continue ;
		}
		add_history(tmp);
		pre_exec(tmp, msh);
		print_tokens(msh->lexer);
		print_parser(msh->parser);
		parser_backup = msh->parser;
		ft_executer(msh);
		msh->parser = parser_backup;
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
	if (!envp || !envp[0])
	{
		printf("🔥No env no minishell, sorry evaluator🔥\n");
		exit(1);
	}
	setup_signals(S_BASE);
	ft_memset(&msh, 0, sizeof(t_shell));
	ft_minishell(&msh, envp);
	return (EXIT_SUCCESS);
}

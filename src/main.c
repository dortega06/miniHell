/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diespino <diespino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 16:02:11 by diespino          #+#    #+#             */
/*   Updated: 2025/12/02 16:31:36 by diespino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
void	print_env(t_env *env)
{
	while (env)
	{
		printf("%s | %s\n", env->var_name, env->var_value);
		env = env->next;
	}
}

void	print_tokens(t_lexer *lexer)
{
//	printf("\n");
	while (lexer != NULL)
	{
		if (lexer->type == T_GENERAL)
			printf("%d | T_GENERAL   | type=%d | %s\n", 
					lexer->index, lexer->type, lexer->data);
		else if (lexer->type == T_CMD)
			printf("%d | T_CMD       | type=%d | %s\n", 
					lexer->index, lexer->type, lexer->data);
		else if (lexer->type == T_PIPE)
			printf("%d | T_PIPE      | type=%d | %s\n", 
					lexer->index, lexer->type, lexer->data);
		else if (lexer->type == T_REDIR_IN)
			printf("%d | T_REDIR_IN  | type=%d | %s\n", 
					lexer->index, lexer->type, lexer->data);
		else if (lexer->type == T_INFILE)
			printf("%d | T_INFILE    | type=%d | %s\n", 
					lexer->index, lexer->type, lexer->data);
		else if (lexer->type == T_HEREDOC)
			printf("%d | T_HEREDOC   | type=%d | %s\n", 
					lexer->index, lexer->type, lexer->data);
		else if (lexer->type == T_LIMITER)
			printf("%d | T_LIMITER   | type=%d | %s\n", 
					lexer->index, lexer->type, lexer->data);
		else if (lexer->type == T_REDIR_OUT)
			printf("%d | T_REDIR_OUT | type=%d | %s\n", 
					lexer->index, lexer->type, lexer->data);
		else if (lexer->type == T_OUTFILE)
			printf("%d | T_OUTFILE   | type=%d | %s\n", 
					lexer->index, lexer->type, lexer->data);
		else if (lexer->type == T_APPEND)
			printf("%d | T_APPEND    | type=%d | %s\n", 
					lexer->index, lexer->type, lexer->data);
		else
			printf("%d | type=%d | %s\n", 
					lexer->index, lexer->type, lexer->data);
		lexer = lexer->next;
	}
//	printf("\n");
}

void	print_parser(t_parser *parser)
{
	int	i;
	
	i = 0;
	while (parser)
	{
		printf("Node %d: %s\n", i++, parser->cmd);
		parser = parser->next;
	}
}

void	pre_exec(char *tmp, t_shell *msh)
{
	ft_lexer(tmp, &msh->lexer, &msh->exit_status);
	ft_lexer_var(msh);
//	ft_parser(&msh->parser, msh->lexer);
}

void	free_mshell(char *input, char *tmp, t_shell *msh)
{
	free(input);
	free(tmp);
	free_token_lst(&msh->lexer);
//	free_parser(&msh->parser);
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
		if (tmp[0] != 0)
			add_history(tmp);
		if (!ft_strcmp(tmp, "exit"))
		{
			free(tmp);
			free(input);
			break ;
		}
		pre_exec(tmp, msh);
		print_tokens(msh->lexer);
//		print_parser(msh->parser);
		free_mshell(input, tmp, msh);
	}
//	print_env(msh->env);
	free_env_lst(&msh->env);
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_tests.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diespino <diespino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 15:42:39 by diespino          #+#    #+#             */
/*   Updated: 2025/12/11 17:59:26 by diespino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void    print_array(char **array)
{
	int	i;

	i = -1;
        while (array[++i])
                printf("   Arg[%d]:     [%s]\n", i, array[i]);
	i = 0;
//	while (array[i])
//		free(array[i++]);
//	free(array);
}

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
			printf("%d | T_GENERAL   | type=%d | [%s]\n", 
					lexer->index, lexer->type, lexer->data);
		else if (lexer->type == T_CMD)
			printf("%d | T_CMD       | type=%d | [%s]\n", 
					lexer->index, lexer->type, lexer->data);
		else if (lexer->type == T_PIPE)
			printf("%d | T_PIPE      | type=%d | [%s]\n", 
					lexer->index, lexer->type, lexer->data);
		else if (lexer->type == T_REDIR_IN)
			printf("%d | T_REDIR_IN  | type=%d | [%s]\n", 
					lexer->index, lexer->type, lexer->data);
		else if (lexer->type == T_INFILE)
			printf("%d | T_INFILE    | type=%d | [%s]\n", 
					lexer->index, lexer->type, lexer->data);
		else if (lexer->type == T_HEREDOC)
			printf("%d | T_HEREDOC   | type=%d | [%s]\n", 
					lexer->index, lexer->type, lexer->data);
		else if (lexer->type == T_LIMITER)
			printf("%d | T_LIMITER   | type=%d | [%s]\n", 
					lexer->index, lexer->type, lexer->data);
		else if (lexer->type == T_REDIR_OUT)
			printf("%d | T_REDIR_OUT | type=%d | [%s]\n", 
					lexer->index, lexer->type, lexer->data);
		else if (lexer->type == T_OUTFILE)
			printf("%d | T_OUTFILE   | type=%d | [%s]\n", 
					lexer->index, lexer->type, lexer->data);
		else if (lexer->type == T_APPEND)
			printf("%d | T_APPEND    | type=%d | [%s]\n", 
					lexer->index, lexer->type, lexer->data);
		else
			printf("%d | type=%d | [%s]\n", 
					lexer->index, lexer->type, lexer->data);
		lexer = lexer->next;
	}
//	printf("\n");
}

void print_parser(t_parser *parser)
{
    int i = 0;
    t_parser	*tmp;

    tmp = parser;
    while (tmp)
    {
        printf("Node %d:\n", i++);
        
        if (tmp->cmd)
            printf("   cmd:        [%s]\n", tmp->cmd);
        else
            printf("   cmd:        (null)\n");

        printf("   redir_in:   %d\n", tmp->redir_in);
        printf("   redir_out:  %d\n", tmp->redir_out);
        tmp = tmp->next;
    }
}

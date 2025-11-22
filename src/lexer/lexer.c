/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diespino <diespino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 17:03:46 by diespino          #+#    #+#             */
/*   Updated: 2025/11/12 15:04:25 by diespino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/* typedef enum e_token
 * {
 *         T_GENERAL,   // 0
 *       # T_CMD,       // 1 CMD
 *         T_PIPE,      // 2 |
 *         T_REDIR_IN,  // 3 <
 *       # T_INFILE,    // 4 <[INFILE]
 *         T_HEREDOC,   // 5 <<
 *       # T_LIMITER,   // 6 <<[LIMITER]
 *         T_REDIR_OUT, // 7 >
 *       # T_OUTFILE,   // 8 >[OUTFILE]
 *         T_APPEND,    // 9 >>
 *         T_SIZE       // 10
 * }
 * T_CMD	--> COMANDO
 * T_INFILE	--> < [INFILE]
 * T_OUTFILE    --> > [OUTFILE] || >> [OUTFILE]
 * T_LIMITER	--> << [LIMITER]
 *
 * typedef struct s_lexer
 * {
 *	int		index;// num token
 *	char		*data;// token
 *	int		type;// tipo token
 *	struct  s_lexer	*next;// siguiente token
 * }	t_lexer;
 *
 */
static void	lexer_index(t_lexer *lexer)
{
	int	i;

	i = 0;
	while (lexer)
	{
		lexer->index = i;
		lexer = lexer->next;
		i++;
	}
}

static void	lexer_cmd(t_lexer *lexer)
{
	if (lexer->type == T_GENERAL)
		lexer->type = T_CMD;
	while (lexer)
	{
		if (lexer->type == T_PIPE)
			lexer->next->type = T_CMD;
		else if (lexer->type == T_REDIR_IN)
			lexer->next->type = T_INFILE;
		else if (lexer->type == T_INFILE && 
				lexer->next && lexer->next->type == T_GENERAL)
			lexer->next->type = T_CMD;
		else if (lexer->type == T_REDIR_OUT || lexer->type == T_APPEND)
			lexer->next->type = T_OUTFILE;
		else if (lexer->type == T_HEREDOC)
			lexer->next->type = T_LIMITER;
		lexer = lexer->next;
	}
}

// input == tmp == string sin " \t\n\v\f\r" delante y atras
void	ft_lexer(char *input, t_lexer **lexer)
{
	int	i;
	int	type;

	i = 0;
	while (input[i])
	{
		while (ft_isspace(input[i]))
			i++;
		type = get_type(input, i);// clasifica los caracteres
		if (type != T_GENERAL)// si no es una palabra
			treat_special(input, lexer, &i, type);// clasifica metacaracteres
		else if (input[i] == '"' || input[i] == '\'')
		{
			if (!treat_quotes(input, lexer, &i, type))// tokeniza interior de "" y ''
				break ;// si hay error sale del while
		}
		else
			treat_general(input, lexer, &i, type);
	}
	if (!check_syntax(*lexer))
	{
		free_token_lst(lexer);
		return ;
	}
	lexer_cmd(*lexer);
	lexer_index(*lexer);
}

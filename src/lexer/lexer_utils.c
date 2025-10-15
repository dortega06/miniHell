/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diespino <diespino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 16:15:59 by diespino          #+#    #+#             */
/*   Updated: 2025/10/02 16:55:26 by diespino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_isspace(int c)
{
	return (c == ' ' || (c >= '\t' && c <= '\r'));
}

int	get_type(char *input, int i)
{
	if (input[i] == '|')
	{
//		if (input[i + 1] == '|' || input[i - 1] == '|')
//			return (T_PIPE);
//		else if (ft_isspace(input[i + 1]) && ft_isspace(input[i - 1]))
			return (T_PIPE);
	}
	else if (input[i] == '<')
	{
		if (input[i + 1] == '<')
			return (T_HEREDOC);
		return (T_REDIR_IN);
	}
	else if (input[i] == '>')
	{
		if (input[i + 1] == '>')
			return (T_APPEND);
		return (T_REDIR_OUT);
	}
	return (T_GENERAL);
}

// lexer_add_token(string, struct lexer, indice actual, tamano de token, type);
void	lexer_add_token(char *str, t_lexer **lexer, int *i, int size, int type)
{
	t_lexer *new;
	t_lexer *tmp;

	new = ft_calloc(1, sizeof(t_lexer));
	new->data = ft_substr(str, (*i), size);
	new->type = type;
	new->next = NULL;
	if (*lexer == NULL)
		*lexer = new;
	else
	{
		tmp = *lexer;
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = new;
	}
}

void	free_token_lst(t_lexer **lexer)
{
	t_lexer	*tmp;

	if (!lexer || !(*lexer))
		return ;
	while (*lexer)
	{
		tmp = (*lexer)->next;
		free((*lexer)->data);
		free(*lexer);
		*lexer = tmp;
	}
	*lexer = NULL;
}

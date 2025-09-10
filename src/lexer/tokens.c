/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diespino <diespino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 10:59:12 by diespino          #+#    #+#             */
/*   Updated: 2025/09/10 14:18:30 by diespino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <readline/readline.h>
#include "token.h"

t_token_type	token_type(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '|' && str[i + 1] == '\0')
		return (PIPE);
	else if (str[i] == '<' && str[i + 1] == '\0')
		return (REDIR_IN);
	else if (str[i] == '>' && str[i + 1] == '\0')
		return (REDIR_OUT);
	else if (str[i] == '<' && str[i + 1] == '<' && 
			str[i + 2] == '\0')
		return (APPEND);
	else if (str[i] == '>' && str[i + 1] == '>' &&
			str[i + 2] == '\0')
		return (HEREDOC);
	else if (str[i] == '-')// || str[i] == '"' || str[i] == '\'')
		i++;
	while (str[i])
	{
//		while (str[i] == '"' || str[i] == '\'')// && str[i + 1] == '\0')
//			i++;
		if (ft_isalpha(str[i]) || ft_isdigit(str[i]))
			i++;
		else
			return (ERROR);
	}
	return (WORD);
}

void	add_next_token(t_token **tokens, t_token *new)
{
	t_token	*tmp;

	if (!new)
		return ;
	if (!*tokens)
	{
		*tokens = new;
		return ;
	}
	tmp = *tokens;
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = new;
}

t_token	*new_token(t_token_type type, char *str, int pos)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->type = type;
	token->value = ft_strdup(str);
	token->position = pos;
	token->next = NULL;
//	printf("%d | type=%d | %s\n", token->position, token->type, token->value);
	return (token);
}

t_token	*make_tokens(char *str)
{
	int		i;
	int		w_count;
	char    	**words;
	t_token		*tokens;
	t_token_type	type;

	i = 0;
	w_count = 0;
	words = ft_split(str, ' ');
	while (words[w_count])
		w_count++;
	while (i < w_count)
	{
		type = token_type(words[i]);
		if (i == 0)
			tokens = new_token(type, words[i], i);
		else
			add_next_token(&tokens, new_token(type, words[i], i));
		i++;
	}
	return (tokens);
}

void	print_tokens(t_token *token)
{
	while (token)
	{
		printf("%d | type=%d | %s\n", 
			token->position, 
			token->type, 
			token->value);
		token = token->next;
	}
}

int	main(void)
{
	char	*line;
	t_token	*tokens;

	
	while ((line = readline(">> ")) != NULL)
	{
		tokens = make_tokens(line);		
		print_tokens(tokens);
		free(line);
	}
	return (0);
}

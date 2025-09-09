/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diespino <diespino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 10:59:12 by diespino          #+#    #+#             */
/*   Updated: 2025/09/09 15:53:07 by diespino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <readline/readline.h>
#include "token.h"

t_token_type	token_type(char *str)
{
	int	i;
//	int	j;

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
	while (str[i])
	{
		if (ft_isalpha(str[i]) || ft_isdigit(str[i]))
			i++;
		else
			return (ERROR);
	}
	return (WORD);
}

void	new_token(t_token_type type, char *str, int pos)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		return ;
	token->type = type;
	token->value = ft_strdup(str);
	token->position = pos;
	printf("%d | type=%d | %s\n", token->position, token->type, token->value);
}

void	make_tokens(char **word, int nbr)//, t_token_type type)
{
	int		i;
//	t_token		token[nbr];
	t_token_type	type;

	i = 0;
	while (i < nbr)
	{
		type = token_type(word[i]);
		new_token(type, word[i], i);
		i++;
	}
}

void	cut_str(char *str)// falta t_token_type type
{
	int	i;
	int	word_count;
	char    **words;
	
	i = 0;
	word_count = 0;
	words = ft_split(str, ' ');
	while (words[word_count])
		word_count++;
	make_tokens(words, word_count);

}

int	main(void)
{
	char	*line;

	while ((line = readline(">> ")) != NULL)
	{
//		printf("Line | %s\n", line);
		cut_str(line);		
		free(line);
	}
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_shell.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diespino <diespino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 12:42:53 by diespino          #+#    #+#             */
/*   Updated: 2025/12/06 14:03:38 by diespino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "../../includes/minishell.h"
#include "../../libft/libft.h"
#include <stdio.h>
//
// str  --> msh->parser->cmd
//  c	--> ' '
//
// count_words para separar
// find_words para hacer ft_substr()
// podar \" y \'
// msh->num_cmd_args = word_nbr;

int     find_quotes(char *str, int *i);
int     find_words(char *str, char c, int *i);

int	count_words(char *str, char c)
{
	int	i;
	int	words;

	i = 0;
	words = 0;
	while (str[i])
	{
		while (str[i] && str[i] == c)
			i++;
		if (str[i])
			words += find_words(str, c, &i);
		if (str[i])
			find_quotes(str, &i);
	}
	return (words);
}

// recorre string hasta mientras no sea ' '

int	find_words(char *str, char c, int *i)
{
	while (str[*i] && str[*i] != c)
	{
		while (str[*i] && str[*i] != c)
		{
			find_quotes(str, i);
			*i = *i + 1;
		}
		return (1);
	}
	return (0);
}

int	find_quotes(char *str, int *i)
{
	char	quote;
	
	if (str[*i] && ft_isquote(str[*i]))
	{
		quote = str[*i];
		*i = *i + 1;
		while (str[*i] && str[*i] != quote)
			*i = *i + 1;
		return (1);
	}
	return (0);
}

char	**ft_split_shell(char *str, char c)//t_shell *msh
{
	int	i;
	int	word;
	int	start;
	char	**split;
	char	*tmp;
	
	i = 0;
	word = 0;
	start = 0;
	split = malloc(sizeof(char *) * (count_words(str, c) + 1));
	if (!split)
		return (NULL);
	while (str[i])
	{
		while (str[i] && str[i] == c)
		{
			start++;
			i++;
		}
		if (find_words(str, c, &i))
		{
			tmp = ft_substr(str, start, i - start);
			split[word++] = ft_strtrim(tmp, "\"\'");
			free(tmp);
			start = i;
		}
//		msh->num_cmd_args = word;
	}
	split[word] = NULL;
	return (split);
}

int	main(void)
{
	int		i;
	char	**split;
	char	str[30] = "echo \"hola que tal?\"";
	
	split = ft_split_shell(str, ' ');
	i = -1;
	while (split[++i])
		printf("%d: %s\n", i, split[i]);
	i = 0;
	while (split[i])
		free(split[i++]);
	free(split);
	return (0);
}

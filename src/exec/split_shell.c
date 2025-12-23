/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_shell.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diespino <diespino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 16:08:17 by diespino          #+#    #+#             */
/*   Updated: 2025/12/23 18:18:10 by diespino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	find_quote(char *str, int *i)
{
	char	quote;

	quote = str[*i];
	(*i)++;
	while (str[*i] && str[*i] != quote)
		(*i)++;
	if (str[*i] == quote)
		(*i)++;
}

void	is_word(char *str, char c, int *i)
{
	while (str[*i] && str[*i] != c)
	{
		if (ft_isquote(str[*i]))
			find_quote(str, i);
		else
			(*i)++;
	}
}

int	num_of_words(char *str, char c)
{
	int	i;
	int	words;

	i = 0;
	words = 0;
	while (str[i])
	{
		while (str[i] && str[i] == c)
			i++;
		if (!str[i])
			break ;
		words++;
		while (str[i] && str[i] != c)
		{
			if (ft_isquote(str[i]))
				find_quote(str, &i);
			else
				i++;
		}
	}
	return (words);
}

/*char	*remove_quotes(char *str)
{
	int		i;
	int		j;
	int		len;
	char	quote;
	char	*res;

	i = 0;
	j = 0;
	quote = 0;
	len = ft_strlen(str);
//	res = ft_calloc(len + 1, sizeof(char));
	res = malloc(sizeof(char) * (len + 1));
	if (!res)
		return (NULL);
	while (str[i])
	{
		if (!quote && (str[i] == '\'' || str[i] == '"'))
			quote = str[i++];
		else if (quote && str[i] == quote)
		{
			quote = 0;
			i++;
		}
		else
			res[j++] = str[i++];
	}
	return (res);
}*/

char	**split_shell(t_shell *msh, char *str, char c)
{
	char	**split;
	int		i;
	int		start;
	int		word;
	char	*tmp;

	i = 0;
	word = 0;
	start = 0;
	split = malloc(sizeof(char *) * (num_of_words(str, c) + 1));
	while (str[i])
	{
		while (str[i] && ft_isspace(str[i]))
			i++;
		start = i;
		is_word(str, c, &i);
		if (start < i)
		{
			tmp = ft_substr(str, start, i - start);
//			printf("%s", tmp);
			split[word++] = tmp;
		}
	}
	split[word] = NULL;
	msh->count_cmd_args = word;
	return (split);
}

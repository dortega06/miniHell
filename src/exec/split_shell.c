/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_shell.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diespino <diespino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 16:08:17 by diespino          #+#    #+#             */
/*   Updated: 2025/12/10 19:15:23 by diespino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// tengo un string y ' '
// necesito saber cuantas palabras hay
// 	para eso necesito saber si hay comilals
// 		si las hay todo lo que haya entre comillas debeb ir junto

void	find_quote(char *str, int *i)
{
	char	quote;
//	int		j;
//	int		x;

//	j = 0;
	quote = str[*i];
//	printf("QUOTES");
	*i = *i + 1;
	while (str[*i] && str[*i] != quote)
	{
//		x = *i;
//		printf("  QUOTES %d %c\n", j++, str[x]);
		*i = *i + 1;
	}
	*i = *i + 1;
}

void	is_word(char *str, char c, int *i)
{
	int	j;
	
	while (str[*i])
	{
		if (ft_isquote(str[*i]))
		{
			j = *i;
			find_quote(str, &j);
			*i = j;
			return ;
		}
		if (str[*i] == c)
			return;
//		printf("%d words: %d %c\n", i, words, str[i]);
		*i = *i + 1;
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

// char	*ft_substr(const char *s, unsigned int start, size_t len)
char	**split_shell(t_shell *msh, char *str, char c)//t_shell *msh
{
	char	**split;
	char	*tmp;
	int		i;
	int		start;
	int		word;

	i = 0;
	word = 0;
	start = 0;
	split = malloc(sizeof(char *) * (num_of_words(str, c) + 1));
	while (str[i])
	{
		while (str[i] && ft_isspace(str[i]))
		{
			start++;
			i++;
		}
		is_word(str, c, &i);
		tmp = ft_substr(str, start, i - start);
		split[word++] = ft_strtrim(tmp, "\"\'");
		free(tmp);
		start = i;
	}
	split[word] = NULL;
	msh->count_cmd_args = word;
	return (split);
}
/*
int	main(void)
{
	int		i;
	int		j;
	char	**split;
//	char	str[30] = "echo \"hola que\" tal?";
	char    str[30] = "echo \"hola que \"t al?";

	printf("str1: %s\n", str);
//	i = num_of_words(str1, ' ');
//	printf("Words1: %d\n\n", i);

//	printf("str2: %s\n", str2);
//	i = num_of_words(str2, ' ');
//	printf("Words2: %d\n", i);

	split = split_shell(str, ' ');
	i = 0;
	j = 1;
	while (split[i])
		printf("%d: ~%s~\n", j++, split[i++]);
	i = 0;
	while (split[i])
		free(split[i++]);
	free(split);
	return (0);
}*/

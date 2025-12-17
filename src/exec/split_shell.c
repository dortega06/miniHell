/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_shell.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diespino <diespino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 16:08:17 by diespino          #+#    #+#             */
/*   Updated: 2025/12/17 19:01:16 by diespino         ###   ########.fr       */
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
	(*i)++;
	while (str[*i] && str[*i] != quote)
	{
//		x = *i;
//		printf("  QUOTES %d %c\n", j++, str[x]);
		(*i)++;
	}
	if (str[*i] == quote)
		(*i)++;
}

void	is_word(char *str, char c, int *i)
{
//	int	j;
	
	while (str[*i] && str[*i] != c)
	{
/*		if (ft_isquote(str[*i]))
		{
			j = *i;
			find_quote(str, &j);
			*i = j;
			return ;
		}
		if (str[*i] == c)
			return;
		*i = *i + 1;*/
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

static char	**trim_quotes(char **array)
{
	char	*tmp;
	int		i;

	i = 0;
	while (array[i])
	{
		if (ft_isquote(array[i][0]))
		{
			if(array[i][0] == '\"')
				tmp = ft_strtrim(array[i], "\"");
			else
				tmp = ft_strtrim(array[i], "\'");
			free(array[i]);
			array[i] = ft_strdup(tmp);
			free(tmp);
		}
		i++;
	}
	return (array);
}

// char	*ft_substr(const char *s, unsigned int start, size_t len)
char	**split_shell(t_shell *msh, char *str, char c)//t_shell *msh
{
	char	**split;
	int		i;
	int		start;
	int		word;

	i = 0;
	word = 0;
	start = 0;
	split = malloc(sizeof(char *) * (num_of_words(str, c) + 1));
	while (str[i])
	{
/*		if (ft_isspace(str[i]) && str[i++])
			start++;
		is_word(str, c, &i);
		split[word++] = ft_substr(str, start, i - start);
		start = i;*/
		while (str[i] && ft_isspace(str[i]))
			i++;
		start = i;
		is_word(str, c, &i);
		if (start < i)
			split[word++] = ft_substr(str, start, i - start);
	}
	split[word] = NULL;
	trim_quotes(split);
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

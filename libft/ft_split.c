/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diespino <diespino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 13:35:08 by diespino          #+#    #+#             */
/*   Updated: 2025/01/31 16:36:08 by diespino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_words(const char *s, char c)
{
	int	cwords;

	cwords = 0;
	if (!*s)
		return (0);
	while (*s)
	{
		if (*s == c)
		{
			cwords++;
			while (*s == c)
				s++;
		}
		else
			s++;
	}
	cwords++;
	return (cwords);
}

static void	*ft_free(char **memry, size_t aux)
{
	size_t	i;

	i = 0;
	while (i < aux)
	{
		free(memry[i]);
		i++;
	}
	free(memry);
	return (NULL);
}

static void	split_str(char **ptr, char *str, char c, int nwords)
{
	int		i;
	char	*aux;

	i = 0;
	if ((nwords > 0) && *str)
	{
		while (i < (nwords - 1))
		{
			aux = ft_strchr(str, c);
			ptr[i++] = ft_substr(str, 0, aux - str);
			if (ptr == 0)
			{
				ft_free(ptr, i);
				return ;
			}
			while (*aux == c)
				aux++;
			str = aux;
		}
		ptr[i++] = ft_strdup(str);
		ptr[i] = 0;
	}
}

char	**ft_split(const char *s, char c)
{
	int		nwords;
	char	**ptr;
	char	*str;
	char	a[2];

	a[0] = c;
	a[1] = '\0';
	if (s)
	{
		str = ft_strtrim(s, a);
		if (str)
		{
			nwords = count_words(str, c);
			ptr = ft_calloc((nwords + 1), sizeof(char *));
			if (ptr)
				split_str(ptr, str, c, nwords);
			free(str);
			return (ptr);
		}
	}
	return (0);
}

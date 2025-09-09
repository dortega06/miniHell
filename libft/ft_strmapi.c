/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diespino <diespino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 14:04:47 by diespino          #+#    #+#             */
/*   Updated: 2025/02/03 14:11:05 by diespino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(const char	*s, char (*f)(unsigned int, char))
{
	size_t	i;
	char	*str;

	if (!s || !f)
		return (0);
	str = malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (!str)
		return (NULL);
	i = -1;
	while (s[++i])
		str[i] = (*f)(i, s[i]);
	str[i] = '\0';
	return (str);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diespino <diespino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 16:52:31 by diespino          #+#    #+#             */
/*   Updated: 2025/02/03 14:29:30 by diespino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(const char *s, unsigned int star, size_t len)
{
	size_t	i;
	size_t	str_len;
	char	*str;

	if (!s)
		return (NULL);
	str_len = ft_strlen(s);
	if (star >= str_len)
		len = 0;
	if (len > str_len - star)
		len = str_len - star;
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	i = -1;
	while (++i < len)
		str[i] = s[i + star];
	str[i] = '\0';
	return (str);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diespino <diespino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 14:28:48 by diespino          #+#    #+#             */
/*   Updated: 2025/01/21 16:04:05 by diespino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*ptr;
	unsigned char	to_find;

	ptr = (unsigned char *)s;
	to_find = (unsigned char)c;
	while (n--)
	{
		if (*ptr == to_find)
			return ((void *)ptr);
		ptr++;
	}
	return (NULL);
}

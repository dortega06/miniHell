/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_ptr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diespino <diespino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 14:17:54 by diespino          #+#    #+#             */
/*   Updated: 2025/02/24 13:41:13 by diespino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ptr_len(uintptr_t ptr)
{
	int	len;

	len = 0;
	while (ptr)
	{
		len++;
		ptr /= 16;
	}
	return (len);
}

void	ptr_to_hex(uintptr_t ptr)
{
	if (ptr >= 16)
	{
		ptr_to_hex(ptr / 16);
		ptr_to_hex(ptr % 16);
	}
	else
	{
		if (ptr <= 9)
			ft_putchar(ptr + '0');
		else
			ft_putchar(ptr - 10 + 'a');
	}
}

int	ft_print_ptr(unsigned long long ptr)
{
	int	len;

	len = 0;
	if (ptr == 0)
		len += write(1, "(nil)", 5);
	else
	{
		len += write(1, "0x", 2);
		ptr_to_hex(ptr);
		len += ptr_len(ptr);
	}
	return (len);
}

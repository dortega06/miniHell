/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_hex.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diespino <diespino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 17:22:22 by diespino          #+#    #+#             */
/*   Updated: 2025/02/24 13:40:21 by diespino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	hex_len(unsigned int nbr)
{
	int	len;

	len = 0;
	while (nbr)
	{
		len++;
		nbr /= 16;
	}
	return (len);
}

void	to_hex(unsigned int nbr, const char format)
{
	if (nbr >= 16)
	{
		ft_print_hex(nbr / 16, format);
		ft_print_hex(nbr % 16, format);
	}
	else
	{
		if (nbr <= 9)
			ft_putchar(nbr + '0');
		else
		{
			if (format == 'x')
				ft_putchar(nbr - 10 + 'a');
			if (format == 'X')
				ft_putchar(nbr - 10 + 'A');
		}
	}
}

int	ft_print_hex(unsigned int nbr, const char format)
{
	int	len;

	len = 0;
	if (nbr == 0)
		len += write(1, "0", 1);
	else
	{
		to_hex(nbr, format);
		len += hex_len(nbr);
	}
	return (len);
}

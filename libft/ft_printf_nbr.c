/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_nbr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diespino <diespino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 17:20:50 by diespino          #+#    #+#             */
/*   Updated: 2025/02/24 13:38:36 by diespino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_print_nbr(int nbr)
{
	int		nbr_len;
	char	*itoa_result;

	nbr_len = 0;
	if (nbr == 0)
		return (write(1, "0", 1));
	itoa_result = ft_itoa(nbr);
	nbr_len += ft_putstr(itoa_result);
	free(itoa_result);
	return (nbr_len);
}

static int	ft_nbrlen(unsigned int nbr)
{
	int	len;

	len = 0;
	while (nbr)
	{
		len++;
		nbr /= 10;
	}
	return (len);
}

char	*ft_unitoa(unsigned int nbr)
{
	char	*str;
	int		len;

	len = ft_nbrlen(nbr);
	str = malloc(sizeof(char) * (len + 1));
	if (!str)
		return (0);
	if (nbr == 0)
		str[0] = '0';
	str[len--] = '\0';
	while (nbr)
	{
		str[len] = (nbr % 10) + '0';
		nbr /= 10;
		len--;
	}
	return (str);
}

int	ft_unsigned(unsigned int nbr)
{
	int		nbr_len;
	char	*unitoa_result;

	nbr_len = 0;
	if (nbr == 0)
		nbr_len += write(1, "0", 1);
	unitoa_result = ft_unitoa(nbr);
	if (!unitoa_result)
		return (0);
	nbr_len += ft_putstr(unitoa_result);
	free(unitoa_result);
	return (nbr_len);
}

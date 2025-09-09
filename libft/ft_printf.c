/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diespino <diespino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 14:31:55 by diespino          #+#    #+#             */
/*   Updated: 2025/02/24 13:36:59 by diespino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putstr(char *str)
{
	int	i;

	if (str == NULL)
	{
		write(1, "(null)", 6);
		return (6);
	}
	i = -1;
	while (str[++i])
		write(1, &str[i], 1);
	return (i);
}

int	ft_putchar(int c)
{
	write(1, &c, 1);
	return (1);
}

int	ft_percent(void)
{
	write(1, "%", 1);
	return (1);
}

int	ft_formats(va_list args, const char format)
{
	int	format_len;

	if (!args || !format)
		return (0);
	format_len = 0;
	if (format == 'c')
		format_len += ft_putchar(va_arg(args, int));
	else if (format == 's')
		format_len += ft_putstr(va_arg(args, char *));
	else if (format == 'p')
		format_len += ft_print_ptr(va_arg(args, unsigned long long));
	else if (format == 'i' || format == 'd')
		format_len += ft_print_nbr(va_arg(args, int));
	else if (format == 'u')
		format_len += ft_unsigned(va_arg(args, unsigned int));
	else if (format == 'x' || format == 'X')
		format_len += ft_print_hex(va_arg(args, unsigned int), format);
	else if (format == '%')
		format_len += ft_percent();
	return (format_len);
}

int	ft_printf(const char *str, ...)
{
	va_list	args;
	int		i;
	int		print_len;

	if (!str)
		return (0);
	i = 0;
	print_len = 0;
	va_start(args, str);
	while (str[i])
	{
		if (str[i] == '%' && str[i + 1] != '\0')
		{
			print_len += ft_formats(args, str[i + 1]);
			i++;
		}
		else
		{
			write(1, &str[i], 1);
			print_len++;
		}
		i++;
	}
	va_end(args);
	return (print_len);
}

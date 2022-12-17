/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rasilva <rasilva@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 14:39:05 by rasilva           #+#    #+#             */
/*   Updated: 2022/06/03 09:03:21 by rasilva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "ft_printf.h"

int	ft_format(va_list args, const char format)
{
	int	back;

	back = 0;
	if (format == 'c')
		back += ft_putchar(va_arg(args, int));
	else if (format == 's')
		back += ft_putstr(va_arg(args, char *));
	else if (format == 'p')
		back += ft_address(va_arg(args, unsigned long));
	else if (format == 'd' || format == 'i')
		back += ft_putnbr(va_arg(args, int));
	else if (format == 'u')
		back += ft_nbr_u(va_arg(args, unsigned int));
	else if (format == 'x' || format == 'X')
	{
		if (format == 'X')
			back += ft_hex(va_arg(args, unsigned int), "0123456789ABCDEF");
		else
			back += ft_hex(va_arg(args, unsigned int), "0123456789abcdef");
	}
	else if (format == '%')
		back += ft_putchar('%');
	return (back);
}

int	ft_printf(const char *format, ...)
{
	va_list	arg;
	int		back;
	int		i;

	va_start(arg, format);
	back = 0;
	i = 0;
	while (format[i])
	{
		if (format[i] == '%' && ft_strchr("cspdiuxX%", format[i + 1]))
		{
			back += ft_format(arg, format[i + 1]);
			i++;
		}
		else
			back += ft_putchar(format[i]);
		i++;
	}
	va_end(arg);
	return (back);
}

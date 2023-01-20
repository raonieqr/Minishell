/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdos-san <sdos-san@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 13:43:36 by sdos-san          #+#    #+#             */
/*   Updated: 2023/01/19 13:43:39 by sdos-san         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putchar(char c)
{
	write(1, &c, 1);
	return (1);
}

int	ft_putstr(char *str)
{
	int	size;

	if (!str)
	{
		write(1, "(null)", 6);
		return (6);
	}
	size = ft_strlen(str);
	write(1, str, size);
	return (size);
}

int	ft_putnbr(int nbr)
{
	char	*str;
	int		size;

	str = ft_itoa(nbr);
	size = ft_putstr(str);
	free(str);
	return (size);
}

int	ft_nbr_u(unsigned int nbr)
{
	char	*s;
	int		size;

	s = ft_utoa(nbr);
	size = ft_putstr(s);
	free(s);
	return (size);
}

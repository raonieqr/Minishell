/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rasilva <rasilva@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 13:52:26 by rasilva           #+#    #+#             */
/*   Updated: 2022/06/03 08:59:30 by rasilva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

static int	size_number(unsigned int n);

char	*ft_utoa(unsigned int n)
{
	int			size;
	char		*s;

	size = size_number(n);
	s = (char *)malloc(sizeof(char) * (size + 1));
	if (!s)
		return ((void *)0);
	s[size] = '\0';
	if (n == 0)
		s[0] = '0';
	s[size--] = '\0';
	while (n)
	{
		s[size--] = (n % 10) + '0';
		n /= 10;
	}
	return (s);
}

static int	size_number(unsigned int n)
{
	int	size;

	size = 0;
	if (n <= 0)
		size++;
	while (n)
	{
		size++;
		n = n / 10;
	}
	return (size);
}

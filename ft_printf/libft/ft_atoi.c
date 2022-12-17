/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rasilva <rasilva@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/08 13:35:52 by rasilva           #+#    #+#             */
/*   Updated: 2022/05/13 13:56:55 by rasilva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

static	int	check(int a);

int	ft_atoi(const char *nptr)
{
	long	num;
	size_t	r;
	int		a;
	long	aux_number;

	r = 0;
	a = 1;
	num = 0;
	while ((nptr[r] >= '\t' && nptr[r] <= '\r') || nptr[r] == ' ')
		r++;
	if (nptr[r] == '+' || nptr[r] == '-')
	{
		if (nptr[r] == '-')
			a *= -1;
		r++;
	}
	while (nptr[r] >= '0' && nptr[r] <= '9')
	{
		aux_number = num;
		num = (nptr[r] - '0') + (num * 10);
		if (num < aux_number)
			return (check(a));
		r++;
	}
	return (num * a);
}

static	int	check(int a)
{
	if (a > 0)
		return (-1);
	else
		return (0);
}

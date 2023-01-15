/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rasilva <rasilva@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/07 18:41:25 by rasilva           #+#    #+#             */
/*   Updated: 2022/05/09 09:20:34 by rasilva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*str2;
	unsigned char	b;
	size_t			i;

	b = (unsigned char)c;
	str2 = (unsigned char *)s;
	i = 0;
	while (i < n)
	{
		if (*str2 == b)
			return (str2);
		str2++;
		i++;
	}
	return ((void *)0);
}

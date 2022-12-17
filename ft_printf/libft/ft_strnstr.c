/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rasilva <rasilva@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/08 13:26:54 by rasilva           #+#    #+#             */
/*   Updated: 2022/05/09 09:31:46 by rasilva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	auxlen;

	auxlen = ft_strlen(little);
	if (auxlen > len)
		return ((void *)0);
	if (*little == '\0')
		return ((char *)big);
	while (*big && auxlen <= len--)
	{
		if (ft_strncmp((char *)big, little, auxlen) == 0)
			return ((char *)big);
		big++;
	}
	return ((void *)0);
}

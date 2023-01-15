/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rasilva <rasilva@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 13:19:16 by rasilva           #+#    #+#             */
/*   Updated: 2022/05/11 08:49:25 by rasilva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*ptr;
	size_t	size_s;

	size_s = ft_strlen((char *)s);
	if (!s)
		return ((void *)0);
	if (start > size_s)
		return (ft_strdup(""));
	if (size_s - start >= len)
		ptr = malloc((len + 1));
	else
		ptr = malloc((size_s - start + 1));
	if (ptr == ((void *)0))
		return ((void *)0);
	ft_strlcpy(ptr, (s + start), (len + 1));
	return (ptr);
}

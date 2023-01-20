/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdos-san <sdos-san@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 13:48:49 by sdos-san          #+#    #+#             */
/*   Updated: 2023/01/19 13:48:53 by sdos-san         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*ptr;
	size_t	totaloc;

	if (nmemb == 0 || size == 0)
	{
		nmemb = 1;
		size = 1;
	}
	totaloc = nmemb * size;
	if (totaloc / nmemb != size)
		return ((void *)0);
	ptr = malloc(totaloc);
	if (ptr)
		ft_bzero(ptr, totaloc);
	return (ptr);
}

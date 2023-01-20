/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdos-san <sdos-san@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 13:48:59 by sdos-san          #+#    #+#             */
/*   Updated: 2023/01/19 13:49:03 by sdos-san         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalnum(int c)
{
	int	alpha;
	int	digit;

	alpha = ft_isalpha(c);
	digit = ft_isdigit(c);
	if (alpha == 1 || digit == 1)
		return (1);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rasilva <rasilva@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 13:04:24 by rasilva           #+#    #+#             */
/*   Updated: 2022/05/13 13:58:25 by rasilva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strrchr(const char *s, int c)
{
	char	*count;

	count = 0;
	while (*s)
	{
		if (*s == (char)c)
			count = (char *)s;
		s++;
	}
	if (c == 0)
		return ((char *)s);
	return (count);
}

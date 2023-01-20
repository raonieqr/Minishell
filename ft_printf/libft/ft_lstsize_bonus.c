/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdos-san <sdos-san@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 13:51:59 by sdos-san          #+#    #+#             */
/*   Updated: 2023/01/19 13:51:59 by sdos-san         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	size_t	i;

	i = 1;
	if (!lst)
	{
		printf("Lista nula\n");
		return (0);
	}
	while (lst->next != NULL)
	{
		lst = lst->next;
		i++;
	}
	return (i);
}

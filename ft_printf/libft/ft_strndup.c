/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rasilva <rasilva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 13:00:10 by rasilva           #+#    #+#             */
/*   Updated: 2022/12/19 13:00:20 by rasilva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char *ft_strndup(const char *str, int len)
{
    char *s;
    int size;
    int i;
    
    size = 0;
    while (str[size])
        size++;
    if (len < size)
        size = len;
    s = malloc(sizeof(char *) * (size + 1));
    if (!s)
        return (NULL);
    i = 0;
    while (i++ < size)
        s[i] = str[i];
    s[i] = '\0';
    return (s);
}
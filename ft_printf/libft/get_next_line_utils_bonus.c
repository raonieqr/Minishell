/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rasilva <rasilva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 17:05:51 by rasilva           #+#    #+#             */
/*   Updated: 2022/12/14 12:01:30 by rasilva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_len(char *s)
{
	size_t	i;

	i = 0;
	while (*s)
	{
		i++;
		s++;
	}
	return (i);
}

char	*ft_schr(char *s, int c)
{
	if (!s)
		return (0);
	while (*s)
	{
		if (*s == (unsigned char)c)
			return ((char *)s);
		s++;
	}
	if (c == 0)
		return (s);
	return ((void *)0);
}

char	*ft_sjoin(char *mem, char *buff)
{
	size_t	i;
	size_t	j;
	char	*line;

	if (!mem)
	{
		mem = (char *)malloc(1 * sizeof(char));
		mem[0] = '\0';
	}
	if (!mem || !buff)
		return ((void *)0);
	line = malloc(sizeof(char) * ((ft_len(mem) + ft_len(buff)) + 1));
	if (line == (void *)0)
		return ((void *)0);
	i = -1;
	j = 0;
	while (mem[++i])
			line[i] = mem[i];
	while (buff[j] != '\0')
		line[i++] = buff[j++];
	line[ft_len(mem) + ft_len(buff)] = '\0';
	free(mem);
	return (line);
}

char	*ft_get_line(char *mem)
{
	int		i;
	char	*line;

	i = 0;
	if (!mem[i])
		return ((void *)0);
	while (mem[i] && mem[i] != '\n')
		i++;
	line = (char *)malloc(sizeof(char) * (i + 2));
	if (!line)
		return ((void *)0);
	i = 0;
	while (mem[i] && mem[i] != '\n')
	{
		line[i] = mem[i];
		i++;
	}
	if (mem[i] == '\n')
	{
		line[i] = mem[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

char	*ft_new_line(char *mem)
{
	int		i;
	int		j;
	char	*line;

	i = 0;
	while (mem[i] && mem[i] != '\n')
		i++;
	if (!mem[i])
	{
		free(mem);
		return ((void *)0);
	}
	line = (char *)malloc(sizeof(char) * (ft_strlen(mem) - i + 1));
	if (!line)
		return ((void *)0);
	i++;
	j = 0;
	while (mem[i])
		line[j++] = mem[i++];
	line[j] = '\0';
	free(mem);
	return (line);
}

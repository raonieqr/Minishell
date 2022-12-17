/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rasilva <rasilva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 17:55:50 by rasilva           #+#    #+#             */
/*   Updated: 2022/12/14 12:02:49 by rasilva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*read_file(int fd, char *mem)
{
	char	*buff;
	int		read_bytes;

	buff = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buff)
		return ((void *)0);
	read_bytes = 1;
	while (!ft_schr(mem, '\n') && read_bytes > 0)
	{
		read_bytes = read(fd, buff, BUFFER_SIZE);
		if (read_bytes < 0)
			break ;
		buff[read_bytes] = '\0';
		mem = ft_sjoin(mem, buff);
	}
	free(buff);
	if (read_bytes < 0)
		return ((void *)0);
	return (mem);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*mem[4096];

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	mem[fd] = read_file(fd, mem[fd]);
	if (!mem[fd])
		return ((void *)0);
	line = ft_get_line(mem[fd]);
	mem[fd] = ft_new_line(mem[fd]);
	return (line);
}

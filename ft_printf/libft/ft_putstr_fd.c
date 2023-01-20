
#include "libft.h"

void	ft_putstr_fd(char *s, int fd)
{
	while (*s)
	{
		if (!*s || fd < 0)
			break ;
		ft_putchar_fd(*s, fd);
		s++;
	}
}


#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*p;

	p = s;
	i = n;
	while (i != 0)
	{
		*p++ = c;
		i--;
	}
	return (s);
}

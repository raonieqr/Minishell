
#include "libft.h"

size_t	ft_strlcpy(char *dest, const char *src, size_t destsize)
{
	size_t	i;
	size_t	srcsize;

	i = 0;
	srcsize = ft_strlen(src);
	if (srcsize + 1 < destsize)
		ft_memcpy(dest, src, srcsize + 1);
	else if (destsize != 0)
	{
		while (src[i] != '\0' && i < (destsize - 1))
		{
			dest[i] = src[i];
			i++;
		}
		dest[i] = '\0';
	}
	return (srcsize);
}

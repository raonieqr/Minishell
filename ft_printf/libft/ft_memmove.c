
#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t n)
{
	unsigned char		*dest2;
	const unsigned char	*src2;

	dest2 = (unsigned char *)dst;
	src2 = (unsigned char *)src;
	if (dest2 > src2)
	{
		while (n--)
		{
			dest2[n] = src2[n];
		}
	}
	else
	{
		while (n--)
			*(dest2++) = *(src2++);
	}
	return (dst);
}

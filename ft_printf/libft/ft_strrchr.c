
#include "libft.h"

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

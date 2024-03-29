
#include "libft.h"

char	*ft_strjoin(char *s1, char *s2)
{
	size_t	size;
	size_t	size_s1;
	size_t	size_s2;
	char	*dest;

	size_s1 = ft_strlen(s1);
	size_s2 = ft_strlen(s2);
	size = size_s1 + size_s2 + 1;
	dest = malloc(size);
	if (!s1 || !s2)
		return ((void *)0);
	if (dest == (void *)0)
		return ((void *)0);
	ft_strlcpy(dest, s1, size_s1 + 1);
	ft_strlcat(dest + size_s1, s2, size_s2 + 1);
	return (dest);
}

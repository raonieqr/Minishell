
#include "libft.h"

char	*ft_strdup(const char *s)
{
	int		size;
	char	*str;
	char	*p;

	size = ft_strlen(s) + 1;
	str = (char *)malloc(size * 1);
	p = str;
	while (*s)
		*p++ = *s++;
	*p = '\0';
	return (str);
}

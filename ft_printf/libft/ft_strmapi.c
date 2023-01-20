
#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	size_t	i;
	size_t	size;
	char	*s2;

	i = 0;
	size = ft_strlen(s);
	s2 = malloc(size + 1);
	if (!s || !f)
		return ((void *)0);
	if (!s2)
		return ((void *)0);
	while (size > i)
	{
		s2[i] = f(i, s[i]);
		i++;
	}
	s2[i] = '\0';
	return (s2);
}

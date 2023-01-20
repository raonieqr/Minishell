
#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	size_t	i;
	size_t	size;

	i = 0;
	size = ft_strlen(s);
	if (s && f)
	{
		while (size > i)
		{
			(*f)(i, &s[i]);
			i++;
		}
	}
}

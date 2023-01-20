
#include "libft.h"

static int	size_number(unsigned int n);

char	*ft_utoa(unsigned int n)
{
	int			size;
	char		*s;

	size = size_number(n);
	s = (char *)malloc(sizeof(char) * (size + 1));
	if (!s)
		return ((void *)0);
	s[size] = '\0';
	if (n == 0)
		s[0] = '0';
	s[size--] = '\0';
	while (n)
	{
		s[size--] = (n % 10) + '0';
		n /= 10;
	}
	return (s);
}

static int	size_number(unsigned int n)
{
	int	size;

	size = 0;
	if (n <= 0)
		size++;
	while (n)
	{
		size++;
		n = n / 10;
	}
	return (size);
}

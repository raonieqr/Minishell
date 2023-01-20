
#include "ft_printf.h"

static int	ft_len_hex(unsigned long number)
{
	int	counter;

	counter = 0;
	while (number)
	{
		counter++;
		number /= 16;
	}
	return (counter);
}

static char	*ft_to_hex(unsigned int number, char *base)
{
	int		len;
	char	*hex;

	len = ft_len_hex(number);
	hex = (char *)malloc(sizeof(char) * (len + 1));
	if (!hex)
		return ((void *)0);
	hex[len] = '\0';
	while (len != 0)
	{
		hex[len - 1] = base[number % 16];
		number /= 16;
		len--;
	}
	return (hex);
}

int	ft_hex(unsigned int number, char *base)
{
	char	*str;
	int		size;

	if (number == 0)
		return (ft_putchar('0'));
	str = ft_to_hex(number, base);
	size = ft_putstr(str);
	free(str);
	return (size);
}

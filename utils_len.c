#include "minishell.h"

int	size_not_letter(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != c)
		i++;
	return (i);
}

int	size_env(char *str)
{
	int	i;

	i = 0;
	while (str[i] && ft_isalnum(str[i]) && special_checks(str[i]))
		i++;
	if (str[i] == '=')
		i++;
	return (i);
}

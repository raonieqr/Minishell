#include "minishell.h"

int	special_checks(char c)
{
	if (c == '{' || c == '?' || c == '_')
		return (1);
	return (0);
}

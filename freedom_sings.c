#include "minishell.h"

void	freethree_ptrs(char *s, char *s2, char *s3)
{
	free(s);
	free(s2);
	free(s3);
}

void	freetwo_ptrs(char *s, char *s2)
{
	free(s);
	free(s2);
}
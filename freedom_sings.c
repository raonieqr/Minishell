#include "minishell.h"

void	freethree_ptrs(char **s, char **s2, char **s3)
{
	free(*s);
	free(*s2);
	free(*s3);
	*s = NULL;
	*s2 = NULL;
	*s3 = NULL;

}

void	freetwo_ptrs(char **s, char **s2)
{
	free(*s);
	free(*s2);
	*s = NULL;
	*s2 = NULL;
}
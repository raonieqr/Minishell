#include "minishell.h"

t_list	*return_node(t_list *list)
{
	if (list->next || list->cmd)
		return (list);
	else if (!list)
		return (NULL);
	if (list->infile > 2)
		close(list->infile);
	if (list->outfile > 2)
		close(list->outfile);
	free(list);
	list = NULL;
	return (NULL);
}

void	close_free(t_list *cur)
{
	if (cur->infile > 2)
		close(cur->infile);
	if (cur->outfile > 2)
		close(cur->outfile);
	free(cur);
}

void	freetwo_voids(t_sh *s, t_env *s2)
{
	if (s)
		free(s);
	if (s2)
		free(s2);
}
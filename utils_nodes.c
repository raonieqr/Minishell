#include "minishell.h"

t_list	*second_last_node(t_list *list)
{
	int		i;
	t_list	*temp;

	i = ft_lstsize(list) - 2;
	temp = list;
	while (i > 0)
	{
		i--;
		temp = temp->next;
	}
	return (temp);
}

void	*change_node(t_list *list)
{
	if (list->infile > 2)
		close(list->infile);
	if (list->outfile > 2)
		close(list->outfile);
	free(list);
	list = NULL;
	return (NULL);
}

void	*node_change(t_list *list, t_list *temp)
{
	if (temp->infile > 2)
		close(temp->infile);
	if (temp->outfile > 2)
		close(temp->outfile);
	free(temp);
	temp = second_last_node(list);
	temp->next = NULL;
	return (NULL);
}

t_list	*return_node(t_list *list, int check, char **args)
{
	t_list	*temp;

	if (check == -20)
	{
		free_split(args);
		ft_freenode(list);
		return (NULL);
	}
	if (!list)
		return (NULL);
	if (!list->cmd)
		change_node(list);
	temp = ft_lstlast(list);
	if (!temp->cmd)
	{
		node_change(list, temp);
		return (NULL);
	}
	temp = list;
	return (list);
}

void	close_free(t_list *cur)
{
	if (cur->infile > 2)
		close(cur->infile);
	if (cur->outfile > 2)
		close(cur->outfile);
	free(cur);
}

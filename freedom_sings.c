#include "minishell.h"

void	free_split(char **splited)
{
	int		pos;

	pos = 0;
	while (splited[pos])
	{
		free(splited[pos]);
		pos++;
	}
	free(splited);
}

void	free_stack(t_list **stack)
{
	t_list	*temp;

	while (*stack)
	{
		temp = *stack;
		*stack = (*stack)->next;
		free(temp);
	}
	*stack = NULL;
	temp = NULL;
}

void	ft_freenode(t_list *cmd)
{
	t_list	*temp;
	t_list	*aux;
	int		i;

	temp = cmd;
	while (temp)
	{
		aux = temp;
		i = -1;
		if (aux->cmd_path)
			free(aux->cmd_path);
		if (aux->cmd)
		{
			while (aux->cmd[++i])
				free(aux->cmd[i]);
			free(aux->cmd);
		}
		if (aux->infile > 2)
			close(aux->infile);
		if (aux->outfile > 2)
			close(aux->outfile);
		temp = temp->next;
		free(aux);
	}
}

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

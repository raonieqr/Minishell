#include "minishell.h"

int	complement_fill_node(t_list *node, char **args, int i)
{
	if (args[i][0] == '>' && args[i][1] == '>')
	{
		ft_get_outfile2(node, args, i);
		return (2);
	}
	else if (args[i][0] != '|' && args[i][0])
	{
		node->cmd = ft_add_cmd(node->cmd, args[i]);
		return (1);
	}
	else
		return (-1);
}

int	fill_node(t_list *node, char **args, int i)
{
	int	check;

	if (args[i][0] == '>' && ft_strlen(args[i]) == 1)
	{
		ft_get_outfile(node, args, i);
		return (2);
	}
	else if (args[i][0] == '<' && ft_strlen(args[i]) == 1)
	{
		ft_get_infile(node, args, i);
		return (2);
	}
	else if (args[i][0] == '<' && args[i][1] == '<')
	{
		ft_get_infile2(node, args, i);
		return (2);
	}
	else
		check = complement_fill_node(node, args, i);
	return (check);
}

int	verifying(t_list *cmds, int check)
{
	if (check < 0)
	{
		free_stack(&cmds);
		return (1);
	}
	return (0);
}

void	ft_add_node(t_list **lst)
{
	t_list	*temp;
	t_list	*cur;
	t_list	*prev;

	temp = *lst;
	if (!temp)
		return (ft_lstadd_back(lst, cmd_init()));
	while (temp)
	{
		prev = cur;
		cur = temp;
		temp = temp->next;
	}
	if ((!cur->cmd))
	{
		close_free(cur);
		if (!(*lst)->next)
			*lst = NULL;
		else
		{
			prev->next = NULL;
			cur = NULL;
		}
	}
	ft_lstadd_back(lst, cmd_init());
}

t_list	*create_nodes(char **args, t_env *new_envp)
{
	t_list	*cmds;
	t_list	*current_node;
	int		i;
	int		check;

	i = 0;
	check = 0;
	current_node = NULL;
	cmds = NULL;
	g_status = 0;
	while (args[i] && args[i][0])
	{
		if (check_for_cmd(args, i))
		{
			i += args[i][0] == '|';
			ft_add_node(&cmds);
		}
		current_node = ft_lstlast(cmds);
		current_node->envp = new_envp;
		check = fill_node(current_node, args, i);
		if (verifying(cmds, check))
			return (NULL);
		i += check;
	}
	return (return_node(cmds));
}

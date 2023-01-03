#include "minishell.h"

static t_list *cmd_init(void)
{
	t_list *cmd;

	cmd = malloc(sizeof(t_list));
	if (!cmd)
		return (NULL);
	cmd->cmd = NULL;
	cmd->cmd_path = NULL;
	cmd->infile = 0;
	cmd->outfile = 1;
	return (cmd);
}

/* JOGAR ṔARA ARQUIVO UTILS*/
void free_split(char **splited)
{
	int pos;

	pos = 0;
	while (splited[pos])
	{
		free(splited[pos]);
		pos++;
	}
	free(splited);
}

int	check_for_cmd(char **input, int i)
{
	if (i == 0 || input[i][0] == '|')
	{
		if (input[i][0] == '|' && (!input[i + 1] && !input[i + 1][0]))
			return (ft_printf("Pipe without arguments\n"));
		return (1);
	}
	return (0);
}


char **ft_add_cmd(char **cmd, char *args)
{
	char **new_cmd;
	int	i;
	int	size;

	i = 0;
	size  = 0;
	while (cmd[size])
		size++;
	new_cmd = malloc(sizeof(char **) * (size + 2));
	if (!new_cmd)
		//ERROR
	new_cmd[size + 1] = NULL;
	while (i < size + 1)
	{
		new_cmd[i] = ft_strdup(cmd[i]);
		i++;
	}
	new_cmd[i] = ft_strdup(args);
	free_split(cmd);
	return (new_cmd);
}

int	fill_node(t_list *node, char **args, int i)
{
	if (args[i][0] == '>' && !args[i][1])
		return (ft_get_outfile(node, args, i));
	else if (args[i][0] == '<' && !args[i][1])
		return (ft_get_outfile2(node, args, i));
	else if (args[i][0] == '<' && args[i][1] == '<')
		return (ft_get_infile2(node, args, i));
	else if (args[i][0] == '>' && args[i][1] == '>')
		return (ft_get_infile(node, args, i));
	else if (args[i][0] != '|')
		node->cmd = ft_add_cmd(node->cmd, args[i]);
	else
	{
		//ft_printf("Error \n");
		return (-1);
	}
	return (0);
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

t_list *create_nodes(char **args)
{
	t_list	*cmds;
	t_list	*current_node;
	int		i;
	int		check;

	i = 0;
	while (args[i] && args[i][0])
	{
		if (check_for_cmd(args, i))
		{
			i += args[i][0] == '|';
			ft_lstadd_back(&cmds, ft_lstnew(cmd_init()));
		}
		current_node = ft_lstlast(cmds);
		check  = fill_node(current_node, args, i);
		if (check < 0)
		{
			free_stack(&cmds);
			return (NULL);
		}
		if (!cmds)
			break;
		i++;
	}
	//free_split(&temp[1]);
	free_split(args);
	return (cmds);
}

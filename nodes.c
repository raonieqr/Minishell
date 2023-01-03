#include "minishell.h"

static t_param *cmd_init(void)
{
	t_param *cmd;

	cmd = malloc(sizeof(t_param));
	if (!cmd)
		return (NULL);
	cmd->cmd = NULL;
	cmd->path = NULL;
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
	if (i == 0 || args[i][0] == '|')
	{
		if (args[i][0] == '|' && (!args[i + 1] && !args[i + 1][0]))
			return (ft_print("Pipe without arguments\n"));
		return (1);
	}
	return (0);
}

int	fill_node(t_list *node, char **args, int i)
{
	if (args[i][0] == '>' && !args[i][1])
		return () 		//set >
	else if (args[i][0] == '<' && !args[i][1])
		return () 		//set <
	else if (args[i][0] == '<' && args[i][1] == '<')
		return () 		//set <<
	else if (args[i][0] == '>' && args[i][1] == '>')
		return () 		//set >>
	else if (args[i][0] != '|')
		return () 		//fill args
	else
	{
		//ft_printf("Error \n");
		return (-1);
	}
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
			ft_lstadd_back(&cmds, ft_lstnew(mini_init()));
		}
		current_node = ft_lslast(cmds);
		check  = fill_node(current_node, args, i);
		if (check < 0)
			return (free_stack(cmds));
		if (!cmds)
			break;
		i++;
	}
	free_split(&temp[1]);
	free_split(&args);
	return (cmds[0]);
}

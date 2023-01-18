#include "minishell.h"

t_list	*cmd_init(void)
{
	t_list	*cmd;

	cmd = malloc(sizeof(t_list));
	if (!cmd)
		return (NULL);
	cmd->cmd = NULL;
	cmd->cmd_path = NULL;
	cmd->infile = 0;
	cmd->outfile = 1;
	cmd->next = NULL;
	cmd->children = 0;
	return (cmd);
}

int	check_for_cmd(char **input, int i)
{
	if (i == 0 || (input[i][0] == '|' && ft_strlen(input[i]) == 1))
	{
		if (input[i][0] == '|' && (!input[i + 1] && !input[i + 1][0]))
			return (ft_perror(2, NULL, PIPERR));
		return (1);
	}
	return (0);
}

int	cmd_len(char **n_cmd, int i)
{
	if (!n_cmd)
		i = 0;
	else
	{
		while (n_cmd[i])
			i++;
	}
	return (i);
}

char	**ft_add_cmd(char **n_cmd, char *args)
{
	char	**new_cmd;
	int		i;
	int		size;

	i = 0;
	size = cmd_len(n_cmd, i);
	new_cmd = malloc(sizeof(char **) * (size + 2));
	if (!new_cmd)
		ft_perror(2, NULL, MALLOC_ERR);
	new_cmd[size + 1] = NULL;
	while (i < size)
	{
		new_cmd[i] = ft_strdup(n_cmd[i]);
		free(n_cmd[i]);
		i++;
	}
	new_cmd[i] = ft_strdup(args);
	if (n_cmd)
		free(n_cmd);
	return (new_cmd);
}

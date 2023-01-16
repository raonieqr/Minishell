#include "minishell.h"

char	*cmd_prompt(char *input)
{
	char	*temp;

	input = change_special_char(input);
	temp = input;
	input = ft_strtrim(input, " ");
	free(temp);
	return (input);
}

char	*ft_new_trim(char *cmd)
{
	char	*temp;

	temp = NULL;
	if (cmd[0] == '\'' || cmd[ft_strlen(cmd) - 1] == '\'')
		temp = ft_strtrim(cmd, "\'");
	else if (cmd[0] == '\"' || cmd[ft_strlen(cmd) - 1] == '\"')
		temp = ft_strtrim(cmd, "\"");
	else
		temp = ft_strdup(cmd);
	if (temp)
	{
		free(cmd);
		cmd = temp;
	}
	return (cmd);
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
		while (aux->cmd[++i])
			free(aux->cmd[i]);
		if (aux->cmd)
			free(aux->cmd);
		if (aux->infile > 2)
			close(aux->infile);
		if (aux->outfile > 2)
			close(aux->outfile);
		temp = temp->next;
		free(aux);
	}
}

int	check_double_pipe(char **cmds)
{
	int	i;

	i = 0;
	while (cmds[i])
	{
		if (cmds[i + 1])
		{
			if (cmds[i][0] == '|' && cmds[i + 1][0] == '|')
			{
				ft_perror(2, NULL, PIPERR);
				return (1);
			}
		}
		i++;
	}
	return (0);
}

char	*check_temp(char *temp, char *input, int i)
{
	char	*temp2;
	char	*aux;

	temp2 = temp;
	if (check_operator(&input[i]) == 2)
	{
		aux = ft_substr(input, i, 2);
		temp = ft_strjoin(temp, aux);
		i++;
	}
	else
	{
		aux = return_char(input[i]);
		temp = ft_strjoin(temp, aux);
	}
	freetwo_ptrs(&temp2, &aux);
	return (temp);
}

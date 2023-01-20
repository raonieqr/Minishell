#include "minishell.h"

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

char	*check_temp(char *temp, char *input, int *i)
{
	char	*temp2;
	char	*aux;
	int		int_temp;

	temp2 = temp;
	int_temp = *i;
	if (check_operator(&input[int_temp]) == 2)
	{
		aux = ft_substr(input, int_temp, 2);
		temp = ft_strjoin(temp, aux);
		int_temp++;
	}
	else
	{
		aux = return_char(input[int_temp]);
		temp = ft_strjoin(temp, aux);
	}
	freetwo_ptrs(&temp2, &aux);
	*i = int_temp;
	return (temp);
}

int	return_swap(char ****cmds, char **tmp)
{
	char	***s;

	s = *cmds;
	*s = tmp;
	*cmds = s;
	return (0);
}

void	exec_exit(t_list *cmds, t_env *envp)
{
	free_split(envp->env);
	ft_freenode(cmds);
	free(envp);
	exit(g_status);
}

int check_redir(char *prompt)
{
	char **splited;
	int	pos;

	pos = 0;
	splited = ft_split(prompt, ' ');
	if (!splited)
		return (1);
	while (splited[pos])
	{
		if (check_operator(splited[pos]) && !splited[pos + 1])
		{
			free_split(splited);
			write(2, "syntax error near unexpected token `<'\n", 39);
			g_status = 258;
			return (1);
		}
		if ((check_operator(splited[pos + 1]) && check_operator(splited[pos])) && (splited[pos][0] != '|' || splited[pos + 1][0] == '|'))
		{
			free_split(splited);
			write(2, "syntax error near unexpected token `<'\n", 39);
			g_status = 258;
			return (1);
		}
		pos++;
	}
	free_split(splited);
	return (0);
}
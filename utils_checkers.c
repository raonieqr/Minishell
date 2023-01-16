#include "minishell.h"

int	check_builtin(t_list *cmds)
{
	if (!ft_strncmp(cmds->cmd[0], "cd", 2) && ft_strlen(cmds->cmd[0]) == 2
		&& !cmds->next)
		return (1);
	else if (!ft_strncmp(cmds->cmd[0], "export", 6)
		&& ft_strlen(cmds->cmd[0]) == 6 && !cmds->next)
		return (1);
	else if (!ft_strncmp(cmds->cmd[0], "unset", 5)
		&& ft_strlen(cmds->cmd[0]) == 5 && !cmds->next)
		return (1);
	else if (!ft_strncmp(cmds->cmd[0], "exit", 4)
		&& ft_strlen(cmds->cmd[0]) == 4 && !cmds->next)
		return (1);
	else
		return (0);
}

int	has_output(char *cmd)
{
	if (!ft_strncmp(cmd, "pwd", 3) && ft_strlen(cmd) == 3)
		return (1);
	else if (!ft_strncmp(cmd, "env", 3) && ft_strlen(cmd) == 3)
		return (1);
	else if (!ft_strncmp(cmd, "echo", 4) && ft_strlen(cmd) == 4)
		return (1);
	return (0);
}

int	check_pipe(t_sh *cmd)
{
	char	*tmp;

	tmp = ft_strtrim(cmd->prompt, " ");
	if (tmp[0] == '|' || tmp[ft_strlen(tmp) - 1] == '|')
	{
		ft_perror(2, NULL, PIPE);
		ft_free(&tmp);
		return (1);
	}
	ft_free(&tmp);
	return (0);
}

int	check_quote(char *input)
{
	int	i;
	int	d_quote;
	int	s_quote;

	d_quote = 0;
	s_quote = 0;
	i = 0;
	while (input[i])
	{
		if (input[i] == 39 && !s_quote && !d_quote)
			s_quote++;
		else if (input[i] == 39 && !d_quote)
			s_quote--;
		else if (input[i] == '"' && !s_quote && !d_quote)
			d_quote++;
		else if (input[i] == '"' && !s_quote)
			d_quote--;
		i++;
	}
	if (s_quote || d_quote)
		return (1);
	return (0);
}

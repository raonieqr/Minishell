#include "minishell.h"

int special_checks(char c)
{
	if (c == '{' || c == '?' || c == '_')
		return (1);
	return (0);
}

int has_output(char *cmd)
{
	if (!ft_strncmp(cmd, "pwd", 3) && ft_strlen(cmd) == 3)
		return (1);
	else if (!ft_strncmp(cmd, "env", 3) && ft_strlen(cmd) == 3)
		return (1);
	else if (!ft_strncmp(cmd, "echo", 4) && ft_strlen(cmd) == 4)
		return (1);
	return (0);
}

int check_builtin(t_list *cmds)
{
	if (!ft_strncmp(cmds->cmd[0], "cd", 2) && ft_strlen(cmds->cmd[0]) == 2 && !cmds->next)
		return (1);
	else if (!ft_strncmp(cmds->cmd[0], "export", 6) && ft_strlen(cmds->cmd[0]) == 6 && !cmds->next)
		return (1);
	else if (!ft_strncmp(cmds->cmd[0], "unset", 5) && ft_strlen(cmds->cmd[0]) == 5 && !cmds->next)
		return (1);
	else if (!ft_strncmp(cmds->cmd[0], "exit", 4) && ft_strlen(cmds->cmd[0]) == 4 && !cmds->next)
		return (1);
	else
		return (0);
}

// char *change_char(char *prompt)
// {
// 	int i;

// 	i = 0;
// 	while (prompt[i])
// 	{
// 		if (prompt[i] == ';' || prompt[i] == '\\')
// 			prompt[i] = ' ';
// 		i++;
// 	}
// 	return (change_special_char(prompt));
// }
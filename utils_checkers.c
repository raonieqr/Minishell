#include "minishell.h"

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

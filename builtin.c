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

int	is_builtin(char **cmd)
{
	char	*command;

	if (!cmd || !cmd[0])
		return (0);
	command = to_lower(cmd[0]);
	if (!ft_strncmp(command, "pwd", 3) && ft_strlen(command) == 3)
		return (1);
	else if (!ft_strncmp(command, "cd", 2) && ft_strlen(command) == 2)
		return (1);
	else if (!ft_strncmp(command, "env", 3) && ft_strlen(command) == 3)
		return (1);
	else if (!ft_strncmp(command, "export", 6) && ft_strlen(command) == 6)
		return (2);
	else if (!ft_strncmp(command, "echo", 4) && ft_strlen(command) == 4)
		return (1);
	else if (!ft_strncmp(command, "unset", 5) && ft_strlen(command) == 5)
		return (2);
	else if (!ft_strncmp(command, "exit", 4) && ft_strlen(command) == 4)
		return (2);
	return (0);
}

int	exec_builtin(t_list *cmds, t_env *envp)
{
	if (!ft_strncmp(cmds->cmd[0], "pwd", 3) && ft_strlen(cmds->cmd[0]) == 3)
		return (exec_pwd());
	else if (!ft_strncmp(cmds->cmd[0], "echo", 4)
			&& ft_strlen(cmds->cmd[0]) == 4)
		return (exec_echo(cmds->cmd));
	else if (!ft_strncmp(cmds->cmd[0], "env", 3)
			&& ft_strlen(cmds->cmd[0]) == 3)
		exec_env(envp);
	else if (!ft_strncmp(cmds->cmd[0], "cd", 2) && ft_strlen(cmds->cmd[0]) == 2
			&& !cmds->next)
		return (exec_cd(cmds));
	else if (!ft_strncmp(cmds->cmd[0], "export", 6)
			&& ft_strlen(cmds->cmd[0]) == 6 && !cmds->next)
		exec_exports(cmds->cmd[1], envp);
	else if (!ft_strncmp(cmds->cmd[0], "unset", 5)
			&& ft_strlen(cmds->cmd[0]) == 5 && !cmds->next)
		exec_unset(cmds->cmd[1], envp);
	else if (!ft_strncmp(cmds->cmd[0], "exit", 4)
			&& ft_strlen(cmds->cmd[0]) == 4 && !cmds->next)
		exit(g_status);
	else
		return (127);
	return (0);
}

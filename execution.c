#include "minishell.h"

int	matrix_len(char **matrix)
{
	int	i;

	i = 0;
	if (!matrix)
		return (0);
	while (matrix[i])
		i++;
	return (i);
}

char	*test_path(char **cmd)
{
	char	**new_path;
	char	*env_path;

	env_path = getenv("PATH");
	new_path = ft_split(env_path + 5, ':');
	return (test_access(new_path, cmd));
}

char	*test_access(char **path, char **cmd)
{
	char	*temp;
	char	*cmd_path;
	int		i;

	i = -1;
	while (path[++i])
	{
		if (access(cmd[0], F_OK | X_OK) == 0)
			return (cmd[0]);
		temp = ft_strjoin(path[i], "/");
		cmd_path = ft_strjoin(temp, cmd[0]);
		free(temp);
		if (access(cmd_path, F_OK | X_OK) == 0)
			return (cmd_path);
		free(cmd_path);
	}
	return (0);
}

DIR	*check_cmd(t_list *cmds)
{
	DIR		*dir;
	char	**s;

	dir = NULL;
	if (cmds->cmd && cmds->cmd[0])
		dir = opendir(cmds->cmd[0]);
	if (cmds->cmd && cmds->cmd[0] && ft_strchr(cmds->cmd[0], '/') && !dir)
	{
		s = ft_split(cmds->cmd[0], '/');
		cmds->cmd_path = ft_strdup(cmds->cmd[0]);
		cmds->cmd[0] = s[matrix_len(s) - 1];
		//free split
		free(s);
	}
	else if (cmds->cmd && cmds->cmd[0] && !dir)
	{
		cmds->cmd_path = test_path(cmds->cmd);
		if (!cmds || !cmds->cmd[0] || !cmds->cmd[0][0])
			ft_perror(127, NULL, 1);
	}
	return (dir);
}

int	get_path(t_list *cmds)
{
	DIR	*dir;

	dir = check_cmd(cmds);
	if (!is_builtin(cmds->cmd) && dir && cmds && cmds->cmd_path)
		return (ft_perror(126, cmds->cmd[0], 0));
	else if (!is_builtin(cmds->cmd) && cmds && cmds->cmd_path
			&& access(cmds->cmd_path, F_OK) == -1)
		return (ft_perror(127, cmds->cmd_path, 0));
	else if (!is_builtin(cmds->cmd) && cmds && cmds->cmd_path
			&& access(cmds->cmd_path, X_OK) == -1)
		return (ft_perror(126, cmds->cmd[0], 1));
	if (dir)
		closedir(dir);
	return (0);
}

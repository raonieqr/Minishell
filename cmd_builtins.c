#include "minishell.h"

int	exec_echo(char **cmd)
{
	int	i;
	int	flag;
	int	j;

	i = 1;
	flag = 0;
	j = 1;
	if (!cmd[1])
		printf("\n");
	while (!ft_strncmp(cmd[i], "-n", 2))
	{
		while (cmd[i][j] == 'n')
			j++;
		if (!cmd[i][j])
			flag = 1;
		i++;
	}
	while (cmd[i])
	{
		printf("%s", cmd[i]);
		if (!cmd[i + 1] && flag == 0)
			printf("\n");
		if (cmd[i + 1])
			printf(" ");
		i++;
	}
	return (0);
}

int	exec_cd(t_list *cmds, t_env *envp)
{
	char	var[4096];

	getcwd(var, 4095);
	if (!cmds->cmd[1])
	{
		if (chdir(ft_get_env(envp->env, "HOME")) == -1)
			return (ft_perror(127, cmds->cmd[1], 0));
		exec_exports(ft_strjoin("PWD=", var), envp);
		return (0);
	}
	if (chdir(cmds->cmd[1]) == -1)
		return (ft_perror(127, cmds->cmd[1], 0));
	else
	{
		exec_exports(ft_strjoin("PWD=", var), envp);
		return (0);
	}
}

int	exec_pwd(void)
{
	char	var[4096];

	getcwd(var, 4095);
	printf("%s", var);
	printf("\n");
	return (0);
}

void	exec_env(t_env *envp)
{
	int	i;

	i = -1;
	while (envp->env[++i])
		printf("%s\n", envp->env[i]);
}

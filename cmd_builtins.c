#include "minishell.h"

void	print_break_line(char **cmd)
{
	if (!cmd[1])
		printf("\n");
}

int	exec_echo(char **cmd)
{
	int	i;
	int	flag;
	int	j;

	i = 0;
	flag = 0;
	j = 1;
	print_break_line(cmd);
	while (!ft_strncmp(cmd[++i], "-n", 2))
	{
		while (cmd[i][j] == 'n')
			j++;
		if (!cmd[i][j])
			flag = 1;
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
	char	*var;
	char	*temp;
	char	*temp2;

	set_oldpwd(envp);
	if (!cmds->cmd[1])
	{
		temp2 = ft_get_env(envp->env, "HOME");
		if (chdir(temp2) == -1)
			return (ft_perror(127, cmds->cmd[1], 0));
		var = getcwd(NULL, 0);
		temp = ft_strjoin("PWD=", var);
		exec_exports(temp, envp);
		freethree_ptrs(&temp, &var, &temp2);
	}
	else if (chdir(cmds->cmd[1]) == -1)
		return (ft_perror(127, cmds->cmd[1], 0));
	else
	{
		var = getcwd(NULL, 0);
		temp = ft_strjoin("PWD=", var);
		exec_exports(temp, envp);
		freetwo_ptrs(&temp, &var);
	}
	return (0);
}

int	exec_pwd(void)
{
	char	*var;

	var = getcwd(NULL, 0);
	printf("%s", var);
	printf("\n");
	free(var);
	return (0);
}

void	exec_env(t_env *envp)
{
	int	i;

	i = -1;
	while (envp->env[++i])
		printf("%s\n", envp->env[i]);
}

#include "minishell.h"

char *to_lower(char *cmd)
{
	int i;
	char *new_cmd;

	new_cmd = malloc((ft_strlen(cmd) + 1));
	if (!new_cmd)
		return (NULL);
	i = 0;
	while (cmd[i])
	{
		new_cmd[i] = ft_tolower(cmd[i]);
		i++;
	}
	new_cmd[i] = '\0';
	return (new_cmd);
}

int is_builtin(char **cmd)
{
	char *command;

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

void exec_echo(char **cmd)
{
	int i;
	int flag;
	int	j;

	i = 0;
	flag = 0;
	j = 1;
	while (!ft_strncmp(cmd[++i], "-n", 2))
	{
		while(cmd[i][++j] == 'n');
		if (!cmd[i][j])
			flag = 1;
		else
			break;
	}
	if (flag == 1)
		i--;
	while (cmd[i])
	{
		printf("%s", cmd[i]);
		if (!cmd[i + 1] && flag == 0)
			printf("\n");
		if (cmd[i + 1])
			printf(" ");
		i++;
	}
}

int exec_builtin(t_list *cmds, t_env *envp)
{
	if (!ft_strncmp(cmds->cmd[0], "pwd", 3) && ft_strlen(cmds->cmd[0]) == 3)
		exec_pwd();
	else if (!ft_strncmp(cmds->cmd[0], "echo", 4) && ft_strlen(cmds->cmd[0]) == 4)
		exec_echo(cmds->cmd);
	else if (!ft_strncmp(cmds->cmd[0], "cd", 2) && ft_strlen(cmds->cmd[0]) == 2 && !cmds->next)
		return(exec_cd(cmds));
	else if (!ft_strncmp(cmds->cmd[0], "export", 6) && ft_strlen(cmds->cmd[0]) == 6 && !cmds->next)
		exec_exports(cmds->cmd[1], envp);
	else if (!ft_strncmp(cmds->cmd[0], "unset", 5) && ft_strlen(cmds->cmd[0]) == 5 && !cmds->next)
		exec_unset(cmds->cmd[1], envp);
	else if (!ft_strncmp(cmds->cmd[0], "exit", 4) && ft_strlen(cmds->cmd[0]) == 4 && !cmds->next)
		exit(g_status);
	else
		return (127);
	return (0);
}

int exec_cd(t_list *cmds)
{
	char	var[4096];

	getcwd(var, 4095);
	if (!cmds->cmd[1])
	{
		printf("%s\n", ft_get_env(cmds->envp->env, "HOME"));
		if (chdir(ft_get_env(cmds->envp->env, "HOME")) == -1)
		{
			perror(cmds->cmd[1]);
			return(1);
		}
	}
	if (chdir(cmds->cmd[1]) == -1)
	{
		perror(cmds->cmd[1]);
		return(1);
	}
	else
	{
		exec_unset("PWD", cmds->envp);
		exec_exports(ft_strjoin("PWD=", var), cmds->envp);
		return (0);
	}
}

void exec_pwd(void)
{
	char	var[4096];

	getcwd(var, 4095);
	printf("%s", var);
	printf("\n");
}

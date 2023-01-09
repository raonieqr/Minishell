#include "minishell.h"

char	*to_lower(char *cmd)
{
	int		i;
	char	*new_cmd;

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

void	exec_echo(char **cmd)
{
	int	i;
	int	flag;

	i = 1;
	flag = 0;
	if ((!ft_strncmp(cmd[i], "-n", 2)) && ft_strlen(cmd[i]) == 2)
	{
		flag = 1;
		i++;
	}
	while (cmd[i])
	{
		printf("%s", cmd[i]);
		if (!cmd[i + 1] && !flag)
			printf("\n");
		if (cmd[i + 1])
			printf(" ");
		i++;
	}
}

int	exec_builtin(t_list *cmds)
{
	if (!ft_strncmp(cmds->cmd[0], "pwd", 3) && ft_strlen(cmds->cmd[0]) == 3
		&& !cmds->next)
	{
		exec_pwd();
		return (1);
	}
	else if (!ft_strncmp(cmds->cmd[0], "echo", 4)
			&& ft_strlen(cmds->cmd[0]) == 4 && !cmds->next)
	{
		exec_echo(cmds->cmd);
		return (1);
	}
	else if (!ft_strncmp(cmds->cmd[0], "cd", 2) && ft_strlen(cmds->cmd[0]) == 2
			&& !cmds->next)
	{
		exec_cd(cmds->cmd);
		return (1);
	}
	else if (!ft_strncmp(cmds->cmd[0], "export", 6)
			&& ft_strlen(cmds->cmd[0]) == 6 && !cmds->next)
	{
		printf("export\n");
		return (1);
	}
	else if (!ft_strncmp(cmds->cmd[0], "unset", 5)
			&& ft_strlen(cmds->cmd[0]) == 5 && !cmds->next)
	{
		printf("unset\n");
		return (1);
	}
	else if (!ft_strncmp(cmds->cmd[0], "exit", 4)
			&& ft_strlen(cmds->cmd[0]) == 4 && !cmds->next)
	{
		printf("exit\n");
		return (1);
	}
	return (0);
}

void	exec_cd(char **cmd)
{
	if (!cmd[1])
		return ;
	if (chdir(cmd[1]) == -1)
		perror("cmd");
}

void	exec_pwd(void)
{
	printf("%s", getenv("PWD"));
	printf("\n");
}

// void    exec_unset(char **cmd)
// {
//     int i;

//     i = 0;
//     if (!cmd[1])
//         printf("Error: arguments\n");
//     while()
// }
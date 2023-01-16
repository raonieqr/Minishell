#include "minishell.h"

int	check_exec(t_list *list)
{
	if (get_path(list))
		return (-1);
	child_signals();
	g_status = 127;
	if (!list->cmd_path)
	{
		ft_perror(127, list->cmd[0], 1);
		return (-1);
	}
	execve(list->cmd_path, list->cmd, list->envp->env);
	return (127);
}

void	check_commands(t_list *list)
{
	if (check_builtin(list) || has_output(list->cmd[0]))
	{
		g_status = exec_builtin(list, list->envp);
		return ;
	}
	else
	{
		g_status = check_exec(list);
		if (g_status < 0)
			return ;
		g_status = 127;
		ft_perror(g_status, list->cmd[0], 1);
	}
}

static void	childs_pipe(int *flags, int *fd, t_list *list)
{
	int	i;

	i = 0;
	if (!fork())
	{
		if (!flags[0])
			dup2(fd[0], 0);
		if (list->infile != 0)
			dup2(list->infile, 0);
		if (!flags[1])
			dup2(fd[3], 1);
		if (list->outfile != 1)
			dup2(list->outfile, 1);
		while (i++ < 4)
			close(fd[i]);
		check_commands(list);
		exit(g_status);
	}
}

static void	change_pipe(int *fd)
{
	close(fd[0]);
	close(fd[1]);
	fd[0] = fd[2];
	fd[1] = fd[3];
	pipe(fd + 2);
}

static int	see_pipe(int *fd, t_list *list)
{
	int	childs;
	int	*flags;

	childs = 0;
	flags = (int *)malloc(sizeof(int) * 2);
	flags[0] = 1;
	flags[1] = 0;
	while (list)
	{
		if (!list->next)
			flags[1] = 1;
		else
			flags[1] = 0;
		childs_pipe(flags, fd, list);
		childs++;
		flags[0] = 0;
		change_pipe(fd);
		list = list->next;
	}
	free(flags);
	return (childs);
}

int	check_command_pipe(t_list *list)
{
	int	fd[4];
	int	out;
	int	childs;
	int	i;

	out = dup(0);
	i = 0;
	pipe(fd);
	pipe(fd + 2);
	childs = see_pipe(fd, list);
	while (childs-- > 0)
		waitpid(-1, &g_status, 0);
	if (g_status < 256 && g_status)
		g_status = 127;
	else
		g_status /= 256;
	i = 0;
	while (i++ < 4)
		close(fd[i]);
	dup2(out, 0);
	return (childs);
}

void	loop_command(t_list *cmd_node, t_env *envp)
{
	int	childs;

	childs = 1;
	if (!cmd_node->next)
	{
		if (check_builtin(cmd_node))
		{
			g_status = exec_builtin(cmd_node, envp);
			return ;
		}
		if (!fork())
		{
			if (cmd_node->infile != 0)
				dup2(cmd_node->infile, 0);
			if (cmd_node->outfile != 1)
				dup2(cmd_node->outfile, 1);
			g_status = exec_builtin(cmd_node, cmd_node->envp);
			if (g_status == 127 && (check_exec(cmd_node) == 127))
				ft_perror(127, cmd_node->cmd[0], 1);
			exit(g_status);
		}
		while (childs-- >= 0)
			waitpid(-1, &g_status, 0);
		g_status /= 256;
	}
	else
		check_command_pipe(cmd_node);
}

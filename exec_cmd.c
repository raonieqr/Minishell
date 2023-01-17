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

void	error_fork(t_list *cmd_node)
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
			error_fork(cmd_node);
		while (childs-- >= 0)
			waitpid(-1, &g_status, 0);
		g_status /= 256;
	}
	else
		check_command_pipe(cmd_node);
}

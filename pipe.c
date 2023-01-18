#include "minishell.h"

void	childs_pipe(int *flags, int *fd, t_list *list)
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
		if (g_status < 0)
			g_status = 127;
		exit(g_status);
	}
}

void	change_pipe(int *fd)
{
	close(fd[0]);
	close(fd[1]);
	fd[0] = fd[2];
	fd[1] = fd[3];
	pipe(fd + 2);
}

int	see_pipe(int *fd, t_list *list)
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
	if (g_status < 128 && g_status)
		g_status = 127;
	else
		g_status /= 256;
	i = 0;
	while (i++ < 4)
		close(fd[i]);
	dup2(out, 0);
	return (childs);
}

int	check_double_pipe(char **cmds)
{
	int	i;

	i = 0;
	while (cmds[i])
	{
		if (cmds[i + 1])
		{
			if (cmds[i][0] == '|' && cmds[i + 1][0] == '|')
			{
				ft_perror(2, NULL, PIPERR);
				return (1);
			}
		}
		i++;
	}
	return (0);
}

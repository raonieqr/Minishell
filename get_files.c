
#include "minishell.h"

int	open_file(char *path, int cur_fd, int c_write, int c_append)
{
	int	new_fd;

	if (cur_fd > 2)
		close(cur_fd);
	if (!path)
		return (-1);
	if (!c_write && access(path, F_OK) == -1)
		return (ft_perror(127, NULL, 0) * (-1));
	else if (!c_write && access(path, R_OK) == -1)
		return (ft_perror(1, NULL, 0) - 3);
	else if (c_write && access(path, W_OK) == -1 && !access(path, F_OK))
		return (ft_perror(1, NULL, 0) - 3);
	if (c_write && c_append)
		new_fd = open(path, O_CREAT | O_WRONLY | O_APPEND, 0666);
	else if (c_write && !c_append)
		new_fd = open(path, O_CREAT | O_WRONLY | O_TRUNC, 0666);
	else if (!c_write && cur_fd != -1)
		new_fd = open(path, O_RDONLY);
	else
		new_fd = cur_fd;
	return (new_fd);
}

int	ft_get_outfile(t_list *node, char **args, int i)
{
	int	path;

	path = i + 1;
	if (!args[path])
	{
		ft_perror(2, NULL, SYNTAX);
		return (0);
	}
	node->outfile = open_file(args[path], node->outfile, 1, 0);
	if (node->outfile == -1)
	{
		ft_perror(126, NULL, SYNTAX);
		return (-1);
	}
	return (0);
}

int	ft_get_outfile2(t_list *node, char **args, int i)
{
	int	path;

	path = i + 1;
	if (!args[path])
	{
		ft_perror(2, NULL, SYNTAX);
		return (0);
	}
	node->outfile = open_file(args[path], node->outfile, 1, 1);
	if (node->outfile == -1)
	{
		ft_perror(126, NULL, SYNTAX);
		return (-1);
	}
	return (0);
}

int	ft_get_infile2(t_list *node, char **args, int i)
{
	int	delimiter;

	delimiter = i + 1;
	if (!args[delimiter])
	{
		ft_perror(2, NULL, SYNTAX);
		return (0);
	}
	node->infile = here_docs(args[delimiter]);
	if (node->infile == 0)
	{
		ft_perror(126, NULL, SYNTAX);
		return (-1);
	}
	return (0);
}

int	ft_get_infile(t_list *node, char **args, int i)
{
	int path;

	path = i + 1;
	if (!args[path])
	{
		ft_perror(2, NULL, SYNTAX);
		return (0);
	}
	node->infile = open_file(args[path], node->infile, 0, 0);
	if (node->infile == 0)
	{
		ft_perror(126, NULL, SYNTAX);
		return (-1);
	}
	return (0);
}
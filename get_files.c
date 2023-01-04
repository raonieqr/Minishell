
#include "minishell.h"

int	open_file(char *path, int cur_fd, int c_write, int c_append)
{
	int	new_fd;

	printf("HELOO\n");
	if (cur_fd > 2)
		close (cur_fd);
	if (!path)
		return (-1);
	if (!c_write && access(path, F_OK) == -1)
		printf("ERROR AQUIVO NAO EXISTE\n");
	else if (!c_write && access(path, R_OK) == -1 )
		printf("ERRO SEM PERMISSÃO\n");
	else if (c_write && access(path, W_OK) == -1 && !access(path, F_OK))
		printf("ERRO SEM PERMISSÃO\n");
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

int	ft_get_outfile(t_list* node, char **args, int i)
{
	int	path;

	printf("entrei");
	path = i + 1;
	if (!args[path])
	{
		printf("error fd");
		exit(0);
	}
	node->outfile = open_file(args[path], node->outfile, 1, 0);
	if (node->outfile == -1)
	{
		printf("error outfile");
		return (-1);
	}
	return (0);
}

int ft_get_outfile2(t_list* node, char **args, int i)
{
	int	path;

	path = i + 1;
	if (!args[path])
	{
		printf("error fd");
		exit(0);
	}
	node->outfile = open_file(args[path], node->outfile, 1, 1);
	if (node->outfile == -1)
	{
		return (-1);
	}
	return (0);
}

int ft_get_infile2(t_list* node, char **args, int i)
{
	int	delimiter;

	delimiter = i + 1;
	if (!args[delimiter])
	{
		printf("error fd");
		exit(0);
	}
	node->infile = here_docs(args[delimiter]);
	if (node->infile == -1)
	{
		return (-1);
		//ERROR
	}
	return (0);
}

int ft_get_infile(t_list* node, char **args, int i)
{
	int	path;

	path = i + 1;
	if (!args[path])
	{
		printf("error fd");
		exit(0);
	}
	node->infile = open_file(args[path], node->infile, 0, 0);
	printf("%d\n", node->infile);
	if (node->infile == -1)
	{
		return (-1);
		//ERROR
	}
	return (0);
}
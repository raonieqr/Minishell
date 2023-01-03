
#include "minishell.h"

int	open_file(char *file_path, int cur_fd, int write, int append)
{
	int	new_fd;

	if (cur_fd > 2)
		close (cur_fd);
	if (!file_path)
		printf("erro\n");
	if (access(file_path, F_OK) == -1 && !write)
		printf("erro\n");
		//ERROR AQUIVO NAO EXISTE
	else if (access(file_path, R_OK) == -1 && !write)
		printf("erro\n");
		//ERROR SEM PERMISSÃO
	else if (access(file_path, W_OK) && write && !access(file_path, F_OK))
			printf("erro\n");
		//ERRO SEM PERMISSÃO
	if (write && append)
		new_fd = open(file_path, O_CREAT | O_WRONLY | O_APPEND, 0666);
	else if (!append && write)
		new_fd = open(file_path, O_CREAT | O_WRONLY | O_TRUNC, 0666);
	else if (!write && cur_fd != -1)
		new_fd = open(file_path, O_RDONLY);
	else
		new_fd = cur_fd;
	printf("new fd %d\n", new_fd);
	return (new_fd);
}

int	ft_get_outfile(t_list* node, char **args, int i)
{
	int	file_path;

	file_path = i + 1;
	if (!args[file_path])
		//return (//ERROR);
	node->infile = open_file(args[file_path], node->infile, 1, 0);
	if (node->infile == -1)
	{
		return (-1);
		//ERROR
	}
	return (0);
}

int ft_get_outfile2(t_list* node, char **args, int i)
{
	int	file_path;

	file_path = i + 1;
	if (!args[file_path])
		//return (//ERROR);
	node->infile = open_file(args[file_path], node->infile, 1, 1);
	if (node->infile == -1)
	{
		return (-1);
		//ERROR
	}
	return (0);
}

int ft_get_infile2(t_list* node, char **args, int i)
{
	int	delimiter;

	delimiter = i + 1;
	if (!args[delimiter])
		//return (//ERROR);
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
	int	file_path;

	file_path = i + 1;
	if (!args[file_path])
		//return (//ERROR);
	printf("infile %d\n", node->infile);
	node->infile = open_file(args[file_path], node->infile, 0, 0);
	printf("infile %d\n", node->infile);
	if (node->infile == -1)
	{
		return (-1);
		//ERROR
	}
	return (0);
}
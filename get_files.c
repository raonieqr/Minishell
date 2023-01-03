
#include "minishell.h"

int	open_file(char *file_path, int cur_fd, int write, int append)
{
	int	new_fd;

	if (cur_fd > 2)
		close (cur_fd);
	if (!file_path)
		return (-1);
	if (acess(file_path, F_OK) == -1 && !write)
		//ERROR AQUIVO NAO EXISTE
	else if (acess(file_path, R_OK) == -1 && !write)
		//ERROR SEM PERMISSÃO
	else if (acess(file_path, W_OK) && write && !acess(file_path, F_OK))
		//ERRO SEM PERMISSÃO
	if (write && append)
		new_fd = open(file_path, O_CREAT | O_WRONLY | O_APPEND, 0666);
	else if (!append && write)
		new_fd = open(file_path, O_CREAT | O_WRONLY | O_TRUNC, 0666);
	else if (!write && cur_fd != -1)
		new_fd = open(file_path, O_RDONLY);
	else
		new_fd = cur_fd;
	return (new_fd);
}

int	ft_get_outfile(t_node* node, char *args, int i)
{
	int	file_path;

	file_path = i + 1;
	if (!args[file_path])
		return (//ERROR);
	node->infile = open_file(args[file_path], node->infile, 1, 0);
	if (node->infile == -1)
	{
		//ERROR
	}
}

int ft_get_outfile2(t_node* node, char *args, int i)
{
	int	file_path;

	file_path = i + 1;
	if (!args[file_path])
		return (//ERROR);
	node->infile = open_file(args[file_path], node->infile, 1, 1);
	if (node->infile == -1)
	{
		//ERROR
	}
}

int ft_get_infile2(t_node* node, char *args, int i)
{
	int	delimiter;

	delimiter = i + 1;
	if (!args[delimiter])
		return (//ERROR);
	node->infile = here_docs(args[file_path], node->infile, 0, 0);
	if (node->infile == -1)
	{
		//ERROR
	}

}

int ft_get_infile(t_node* node, char *args, int i)
{
	int	file_path;

	file_path = i + 1;
	if (!args[file_path])
		return (//ERROR);
	node->infile = open_file(args[file_path], node->infile, 0, 0);
	if (node->infile == -1)
	{
		//ERROR
	}
}

#include "minishell.h"

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
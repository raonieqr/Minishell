#include "minishell.h"

int	check_end(char *input, char *delimiter)
{
	if (!ft_strncmp(input, delimiter, ft_strlen(delimiter) + 1))
		return (1);
	//CHECK G_STATUS

	return (0);
}

char *get_input(char *delimiter)
{
	char	*returned_str;
	char	*input;
	char	*temp_str;

	returned_str = NULL;
	input = NULL;
	while (!check_end(input, delimiter))
	{
		temp_str = returned_str;
		returned_str = ft_strjoin(returned_str, input);
		freetwo_ptrs(temp_str, input);
		input = readline(">");
		if (!input)
		{
			//ERROR
		}
		temp_str = input;
		input = ft_strjoin(input, "\n");
		free(temp_str);
	}
	free (input);
	return (returned_str);
}

int	here_docs(char *delimiter)
{
	int		fd[2];
	char	*input;

	input = NULL;
	//G_STATUS;
	if (pipe(fd) == -1)
	{
		//ERROR
		return (-1);
	}
	input = get_input(delimiter);
	write(fd[1], input, ft_strlen(input));
	free(input);
	close(fd[0]);
	//CHECK G_STATUS
	return (fd[0]);
}
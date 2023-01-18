#include "minishell.h"

int	check_end(char *input, char *delimiter)
{
	int	size;
	int	equal;

	equal = 0;
	size = 0;
	if (!input)
		return (1);
	if (!ft_strncmp(input, delimiter, ft_strlen(delimiter)))
		equal = 1;
	if (ft_strlen(delimiter) == (ft_strlen(input) - 1))
		size = 1;
	if (size && equal)
		return (1);
	if (g_status == 130)
		return (1);
	return (0);
}

char	*get_input(char *delimiter)
{
	char	*returned_str;
	char	*input;
	char	*temp_str;

	returned_str = ft_calloc(1, 1);
	input = ft_calloc(1, 1);
	while (!check_end(input, delimiter))
	{
		temp_str = returned_str;
		returned_str = ft_strjoin(returned_str, input);
		freetwo_ptrs(&temp_str, &input);
		input = readline(">");
		if (!input)
		{
			printf("%s (wanted `%s\')\n", HDOC_WARN, delimiter);
			break ;
		}
		temp_str = input;
		input = ft_strjoin(input, "\n");
		free(temp_str);
	}
	free(input);
	return (returned_str);
}

int	here_docs(char *delimiter)
{
	int		fd[2];
	char	*input;

	input = NULL;
	g_status = 0;
	if (pipe(fd) == -1)
	{
		ft_perror(1, NULL, PIPERR);
		return (-1);
	}
	input = get_input(delimiter);
	write(fd[1], input, ft_strlen(input));
	free(input);
	close(fd[1]);
	if (g_status == 130)
	{
		close(fd[0]);
		return (-1);
	}
	return (fd[0]);
}

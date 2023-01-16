#include "minishell.h"

void	check_status(int code)
{
	if (code == MALLOC_ERR)
		write(2, ": error on malloc\n", 19);
	else if (code == SYNTAX)
		write(2, ": syntax error near unexpected token 'newline'\n", 48);
	else if (code == PIPERR || code == PIPE)
		write(2, "minishell: syntax error near unexpected token `|'\n", 51);
	else if (code == QUOTES)
		write(2, "minishell: syntax error unclosed quotes\n", 41);
}

int	ft_perror(int status, char *cmd, int code)
{
	g_status = status;
	if (cmd)
		write(2, cmd, ft_strlen(cmd));
	else
		write(2, "Minishell", 9);
	if (status == 127 && code == 1)
		write(2, ": command not found\n", 21);
	else if (status == 127)
		write(2, ": no such file or directory\n", 29);
	else if (status == 126 && code == 1)
		write(2, ": permission denied\n", 21);
	else if (status == 126)
		write(2, ": Is a directory\n", 18);
	check_status(code);
	return (g_status);
}

int	size_matrix(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

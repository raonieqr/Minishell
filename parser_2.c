#include "minishell.h"

char	*ft_new_trim(char *cmd)
{
	char	*temp;

	temp = NULL;
	if (cmd[0] == '\'' || cmd[ft_strlen(cmd) - 1] == '\'')
		temp = ft_strtrim(cmd, "\'");
	else if (cmd[0] == '\"' || cmd[ft_strlen(cmd) - 1] == '\"')
		temp = ft_strtrim(cmd, "\"");
	else
		temp = ft_strdup(cmd);
	if (temp)
	{
		free(cmd);
		cmd = temp;
	}
	return (cmd);
}

char	*check_temp(char *temp, char *input, int i)
{
	char	*temp2;
	char	*aux;

	temp2 = temp;
	if (check_operator(&input[i]) == 2)
	{
		aux = ft_substr(input, i, 2);
		temp = ft_strjoin(temp, aux);
		i++;
	}
	else
	{
		aux = return_char(input[i]);
		temp = ft_strjoin(temp, aux);
	}
	freetwo_ptrs(&temp2, &aux);
	return (temp);
}

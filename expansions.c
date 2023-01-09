
#include "minishell.h"

int	ft_isspace(char c)
{
	if ((c >= 9 && c <= 13) || c == ' ')
		return (1);
	return (0);
}

int	ft_len_char(char *str)
{
	int	i;

	i = 0;
	while (str[i] && !ft_isspace(str[i]))
		i++;
	return (i);
}

char	*change_var(char *cmd, char *var, char *value, int pos_s)
{
	char	*new_cmd;
	char	*temp;

	temp = ft_substr(cmd, 0, pos_s);
	new_cmd = ft_strjoin(temp, value);
	ft_free(&cmd);
	temp = cmd;
	new_cmd = ft_strjoin(new_cmd, cmd + pos_s + ft_strlen(var) + 1);
	ft_free(&temp);
	return (new_cmd);
}

char	*rmv_char(char *str, int i)
{
	int		j;
	int		k;
	char	*str_1;

	str_1 = malloc((ft_len_char(str) * sizeof(char)));
	j = 0;
	k = 0;
	while (str[j] && j < ft_len_char(str))
	{
		if (j < i)
		{
			str_1[j] = str[k];
			j++;
			k++;
		}
		if (j == i)
			k++;
		if (ft_isspace(str[k]))
			break ;
		str_1[j++] = str[k++];
	}
	str_1[j] = '\0';
	return (str_1);
}

void	expand(char **cmds)
{
	int i;
	int j;

	i = 0;
	while (cmds[i])
	{
		if (is_quote(cmds[i]) == 1)
		{
			cmds[i] = ft_new_trim(cmds[i]);
			i++;
		}
		else
		{
			cmds[i] = ft_new_trim(cmds[i]);
			j = 0;
			while (cmds[i][j])
			{
				if (cmds[i][j] == '$')
				{
					if (cmds[i][j + 1] == '?')
						printf(" \n");
					else
					{
						if (getenv(rmv_char(&cmds[i][j], 0)))
							cmds[i] = change_var(cmds[i], rmv_char(&cmds[i][j],
										0), getenv(rmv_char(&cmds[i][j], 0)),
									j);
						else
							printf("Variable not found\n");
					}
				}
				j++;
			}
			i++;
		}
	}
}
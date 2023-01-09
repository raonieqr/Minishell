
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
	while (str[i] && !ft_isspace(str[i]) && str[i] != '$')
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
	(void)i;
	printf("Len %d\n", ft_len_char(str));
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
		if (ft_isspace(str[k]) || str[k] == '$')
			break ;
		str_1[j++] = str[k++];
	}
	str_1[j] = '\0';
	return (str_1);
}


int ft_ismetachar(char c)
{
	if (c >= 7 && c <= 13)
		return (1);
	if (c >= 33 && c <= 47)
		return (1);
	if (c >= 57 && c <= 64)
		return (1);
	if (c >= 91 && c <= 96)
		return (1);
	if (c >= 123 && c <= 126)
		return (1);
	return (0);
}


char *get_sub(char *str)
{
	int i;
	char *new_str;

	i = 0;
	while (str[i] && !ft_ismetachar(str[i]))
		i++;
	new_str = ft_substr(str, 0, i);
	return (new_str);
}

char *join_three(char *str, int j, char *str2)
{
	char	*return_str;
	char	*str1;
	char	*str3;

	return_str = NULL;
	str1 = ft_substr(str, 0, j);
	if (!getenv(str2))
		return (NULL);
	return_str = ft_strjoin(str1, getenv(str2));
	str3 = ft_substr(str, j + ft_strlen(str2) + 1, ft_strlen(str) - j - ft_strlen(str2) - 1);
	return_str = ft_strjoin(return_str, str3);
	ft_free(&str2);
	ft_free(&str1);
	ft_free(&str3);
	return (return_str);
}

int	expand(char **cmds)
{
	int i;
	int j;
	char *tmp;

	i = 0;
	while (cmds[i])
	{
		if (is_quote(cmds[i]) == 1)
		{
			tmp = cmds[i];
			cmds[i] = ft_new_trim(cmds[i]);
			ft_free(&tmp);
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
						cmds[i] = join_three(cmds[i], j, get_sub(cmds[i] + j + 1));
					if (!cmds[i])
						return (-1);
				}
				j++;
			}
			i++;
		}
	}
	return (0);
}
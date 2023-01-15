
#include "minishell.h"

int ft_isspace(char c)
{
	if ((c >= 9 && c <= 13) || c == ' ')
		return (1);
	return (0);
}

int ft_len_char(char *str)
{
	int i;

	i = 0;
	while (str[i] && !ft_isspace(str[i]) && str[i] != '$')
		i++;
	return (i);
}

char *ft_get_env(char **envp, char *var)
{
    int i;

    i = 0;
    while (envp[i])
    {
        if (!ft_strncmp(envp[i], var, ft_strlen(var)) && envp[i][ft_strlen(var)] == '=')
            break ;
        i++;
    }
    if (envp[i])
        return (ft_substr(envp[i], ft_strlen(var) + 1, \
                            ft_strlen(envp[i]) - ft_strlen(var) - 1));
    return (NULL);
}

char *change_var(char *cmd, char *var, char *value, int pos_s)
{
	char *new_cmd;
	char *temp;

	temp = ft_substr(cmd, 0, pos_s);
	new_cmd = ft_strjoin(temp, value);
	temp = cmd;
	new_cmd = ft_strjoin(new_cmd, cmd + pos_s + ft_strlen(var) + 1);
	ft_free(&temp);
	return (new_cmd);
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

char *join_three(char *str, int j, char *str2, t_env *new_envp, int mode)
{
	char *return_str;
	char *str1;
	char *str3;

	return_str = NULL;
	str1 = ft_substr(str, 0, j);
	if (mode)
	{
		if (!ft_get_env(new_envp->env, str2))
			return (NULL);
		return_str = ft_strjoin(str1, ft_get_env(new_envp->env, str2));
	}
	else
		return_str = ft_strjoin(str1, str2);
	str3 = ft_substr(str, j + ft_strlen(str2) + 1, ft_strlen(str) - j - ft_strlen(str2) - 1);
	return_str = ft_strjoin(return_str, str3);
	freethree_ptrs(&str2, &str1, &str3);
	return (return_str);
}

int expand(char **cmds, t_env *new_envp)
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
						cmds[i] = join_three(cmds[i], j, ft_itoa(g_status), new_envp, 0);
					else
						cmds[i] = join_three(cmds[i], j, get_sub(cmds[i] + j + 1), new_envp, 1);
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
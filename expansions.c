#include "minishell.h"

char	*change_var(char *cmd, char *var, char *value, int pos_s)
{
	char	*new_cmd;
	char	*temp;

	temp = ft_substr(cmd, 0, pos_s);
	new_cmd = ft_strjoin(temp, value);
	temp = cmd;
	new_cmd = ft_strjoin(new_cmd, cmd + pos_s + ft_strlen(var) + 1);
	ft_free(&temp);
	return (new_cmd);
}

char	*get_sub(char *str)
{
	int		i;
	char	*new_str;

	i = 0;
	while (str[i] && !ft_ismetachar(str[i]) && !ft_isspace(str[i]))
		i++;
	new_str = ft_substr(str, 0, i);
	return (new_str);
}

char	*join_three(char *str, int j, char *str2, t_env *new_envp)
{
	char	*return_str;
	char	*str1;
	char	*str3;

	return_str = NULL;
	str1 = ft_substr(str, 0, j);
	str3 = ft_get_env(new_envp->env, str2);
	if (!str3)
		return (NULL);
	return_str = ft_strjoin(str1, str3);
	freetwo_ptrs(&str1, &str3);
	str3 = ft_substr(str, j + ft_strlen(str2) + 1, ft_strlen(str) - j
			+ ft_strlen(str2));
	str1 = return_str;
	return_str = ft_strjoin(return_str, str3);
	free(str);
	freethree_ptrs(&str2, &str1, &str3);
	return (return_str);
}

char	*join_status(char *str, int j, char *str2)
{
	char	*return_str;
	char	*str1;
	char	*str3;

	return_str = NULL;
	str1 = ft_substr(str, 0, j);
	free(str);
	return_str = ft_strjoin(str1, str2);
	str = return_str;
	str3 = ft_substr(str, j + ft_strlen(str2) + 1, ft_strlen(str) - j
			- ft_strlen(str2) - 1);
	return_str = ft_strjoin(return_str, str3);
	free(str);
	freethree_ptrs(&str2, &str1, &str3);
	return (return_str);
}

int	expand(char ***cmds, t_env *new_envp)
{
	int		i;
	int		j;
	char	**tmp;

	i = -1;
	tmp = *cmds;
	while (tmp[++i])
	{
		if (is_quote(tmp[i]) == 1)
			tmp[i] = ft_new_trim(tmp[i]);
		else
		{
			tmp[i] = ft_new_trim(tmp[i]);
			j = 0;
			while (tmp[i][j])
			{
				get_flag(&tmp, &i, &j, new_envp);
				if (j < 0)
					return (-1);
				if (!tmp[i])
					return (return_swap(&cmds, tmp));
			}
		}
	}
	return (return_swap(&cmds, tmp));
}

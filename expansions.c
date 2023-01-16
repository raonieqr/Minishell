#include "minishell.h"

char	*ft_get_env(char **envp, char *var)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], var, ft_strlen(var))
			&& envp[i][ft_strlen(var)] == '=')
			break ;
		i++;
	}
	if (envp[i])
		return (ft_substr(envp[i], ft_strlen(var) + 1, ft_strlen(envp[i])
				- ft_strlen(var) - 1));
	return (NULL);
}

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

char	*join_three(char *str, int j, char *str2, t_env *new_envp)
{
	char	*return_str;
	char	*str1;

	return_str = NULL;
	str1 = ft_substr(str, 0, j);
	if (!ft_get_env(new_envp->env, str2))
		return (NULL);
	return_str = ft_strjoin(str1, ft_get_env(new_envp->env, str2));
	freetwo_ptrs(&str2, &str1);
	return (return_str);
}

char	*join_status(char *str, int j, char *str2)
{
	char	*return_str;
	char	*str1;
	char	*str3;

	return_str = NULL;
	str1 = ft_substr(str, 0, j);
		return_str = ft_strjoin(str1, str2);
		str3 = ft_substr(str, j + ft_strlen(str2) + 1, ft_strlen(str) - j
			- ft_strlen(str2) - 1);
		return_str = ft_strjoin(return_str, str3);
	freethree_ptrs(&str2, &str1, &str3);
	return (return_str);
}

int	expand(char **cmds, t_env *new_envp)
{
	int	i;
	int	j;

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
					expand_var(cmds, i, j, new_envp);
				j++;
			}
			i++;
		}
	}
	return (0);
}

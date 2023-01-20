#include "minishell.h"

int	is_quote(char *str)
{
	int	len;

	len = ft_strlen(str);
	if (str[0] == 39)
	{
		if (str[len - 1] == 39)
			return (1);
	}
	if (str[0] == '"' && str[len - 1] == '"')
		return (2);
	else
		return (0);
}

int	expand_var(char ***cmds, int i, int j, t_env *new_envp)
{
	char	**tmp;

	tmp = *cmds;
	if (tmp[i][j + 1] == '?')
		tmp[i] = join_status(tmp[i], j, ft_itoa(g_status));
	else if (!ft_isspace(tmp[i][j + 1]))
		return (not_env(cmds, i, j, new_envp));
	*cmds = tmp;
	j = j + 1;
	return (0);
}

char	**expand_dir(char **cmds)
{
	int	i;
	int	j;

	i = 0;
	while (cmds[i])
	{
		if (!is_quote(cmds[i]))
		{
			j = 0;
			while (cmds[i][j])
			{
				if (cmds[i][j] == '~')
				{
					if (cmds[i][j + 1] == ' ' || (!cmds[i][j + 1]))
						cmds[i] = change_var(cmds[i], "", getenv("HOME"), j);
					else if (cmds[i][j + 1] == '/')
						cmds[i] = change_var(cmds[i], "/", getenv("HOME"), j);
				}
				j++;
			}
		}
		i++;
	}
	return (cmds);
}

void	set_oldpwd(t_env *envp)
{
	char	*old_pwd;

	old_pwd = ft_strjoin("OLDPWD=", ft_get_env(envp->env, "PWD"));
	exec_exports(old_pwd, envp);
}

#include "minishell.h"

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

char	*expand_var(char **cmds, int i, int j, t_env *new_envp)
{
	if (cmds[i][j + 1] == '?')
		return (cmds[i] = join_three(cmds[i], j, ft_itoa(g_status), \
			new_envp));
	else
		return (cmds[i] = join_status(cmds[i], j, get_sub(cmds[i] + j \
			+ 1)));
	if (!cmds[i])
		return (NULL);
}

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

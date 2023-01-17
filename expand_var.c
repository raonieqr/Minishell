#include "minishell.h"

int	get_flag(char ***tmp, int *i, int *j, t_env *new_env)
{
	int		aux1;
	int		aux2;
	int		flag;
	char	**str;

	aux1 = *i;
	aux2 = *j;
	str = *tmp;
	flag = 0;
	if (str[aux1][aux2] == '$')
		flag = expand_var(&str, aux1, aux2, new_env);
	if (flag < 0)
	{
		aux2 = -1;
		*j = aux2;
		return (-1);
	}
	if (!flag)
		aux2++;
	*i = aux1;
	*j = aux2;
	*tmp = str;
	return (aux2);
}

int	return_cmds(char ***cmds, char **tmp, char *to_free, int i)
{
	free(to_free);
	*cmds = tmp;
	return (i);
}

int	not_env(char ***cmds, int i, int j, t_env *new_envp)
{
	char	*tmp;
	char	*tmp2;
	char	**tmp3;

	tmp3 = *cmds;
	tmp = get_sub(tmp3[i] + j + 1);
	tmp2 = ft_get_env(new_envp->env, tmp);
	if (!tmp2)
	{
		if (1 + ft_strlen(tmp) == ft_strlen(tmp3[i]))
		{
			tmp3 = rmv_str(tmp3, i);
			if (!tmp3 || !tmp3[0])
				return (return_cmds(cmds, tmp3, tmp, -1));
		}
		else
			tmp3[i] = rmv_var(j, ft_strlen(tmp) + j, tmp3[i]);
		return (return_cmds(cmds, tmp3, tmp, 3));
	}
	else
	{
		tmp3[i] = join_three(tmp3[i], j, tmp, new_envp);
		return (return_cmds(cmds, tmp3, tmp2, 0));
	}
	return (0);
}

char	**rmv_str(char **str, int pos)
{
	int		size;
	int		pos_str;
	int		pos_new;
	char	**new;

	size = 0;
	pos_str = 0;
	pos_new = 0;
	while (str[size])
		size++;
	new = ft_calloc(sizeof(char **), size);
	if (!new)
		return (NULL);
	while (str[pos_str])
	{
		if (pos != pos_str)
		{
			new[pos_new] = ft_strdup(str[pos_str]);
			pos_new++;
		}
		free(str[pos_str]);
		pos_str++;
	}
	free(str);
	return (new);
}

char	*rmv_var(int start, int end, char *str)
{
	char	*first;
	char	*second;
	char	*result;

	first = ft_substr(str, 0, start);
	second = ft_substr(str, end + 1, ft_strlen(str) - end - 1);
	if (!first)
		return (second);
	if (!second)
		return (first);
	result = ft_strjoin(first, second);
	free(first);
	free(second);
	return (result);
}

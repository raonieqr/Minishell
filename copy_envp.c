#include "minishell.h"

char	**copy_env(char **envp)
{
	int		len;
	int		i;
	char	**copy;

	len = 0;
	i = -1;
	while (envp[len])
		len++;
	copy = malloc(sizeof(char **) * (len + 1));
	if (!copy)
		return (NULL);
	copy[len] = NULL;
	while (envp[++i])
		copy[i] = ft_strdup(envp[i]);
	return (copy);
}

char	**change_envp(char **env, char *new_env)
{
	int		size;
	char	**var_env;
	int		i;

	i = -1;
	size = size_matrix(env) + 1;
	var_env = malloc(sizeof(char **) * size + 1);
	if (!var_env)
		return (NULL);
	var_env[size] = NULL;
	while (++i < size - 1)
		var_env[i] = ft_strdup(env[i]);
	var_env[i] = ft_strdup(new_env);
	ft_free(env);
	free(new_env);
	return (var_env);
}

char	**rmv_envp(char **env, int i)
{
	int		j;
	int		pos;
	char	**var_env;

	j = 0;
	pos = 0;
	var_env = ft_calloc(sizeof(char **), size_matrix(env));
	if (!var_env)
		return (NULL);
	while (env[pos])
	{
		if (pos != i)
		{
			var_env[j] = ft_strdup(env[pos]);
			free(env[pos]);
			j++;
		}
		pos++;
	}
	free(env);
	return (var_env);
}

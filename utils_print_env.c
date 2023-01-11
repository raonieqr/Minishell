#include "minishell.h"

void	char_copy(char **str, char c)
{
	char	*aux;
	int		len_str;
	int		len_aux;

	len_str = ft_strlen(*str);
	aux = malloc(sizeof(char) * (len_str + 2));
	ft_memcpy(aux, &str, len_str);
	len_aux = ft_strlen(aux);
	aux[len_aux] = c;
	if (*str)
		free(*str);
	*str = aux;
}

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

void	exec_exports(char *cmd, t_env *envp)
{
	char	*var;
	char	*value = NULL;
	char	*new_var;
	char	*tmp;

	if (!cmd)
		return ;
	else if (!(var = get_var(cmd)))
	{	
		perror("export");
		return ;
	}
	else if (!(value = get_value(cmd)))
	{
		perror("export");
		return ;
	}
	new_var = ft_strjoin(var, "");
	new_var = ft_strjoin(new_var, value);
	tmp = new_var;
	if (new_var[0] == '\'')
	{
		new_var = ft_strtrim(new_var, "'");
		ft_free(&tmp);
	}
	else if (new_var[0] == '"')
	{
		new_var = ft_strtrim(new_var, "\"");
		ft_free(&tmp);
	}
	envp->env = change_envp(envp->env, new_var);
}

char	*get_var(char *cmd)
{
	int		i;
	char	*var;
	int		j;

	i = 0;
	j = 0;
	while(cmd[i] && cmd[i] != '=')
		i++;
	if (i == 0 || !cmd[i])
		return (NULL);
	var = malloc(sizeof(char *) * i + 1);
	if (!var)
		return (NULL);
	if (ft_ismetachar(cmd[j]) || ft_isdigit(cmd[j]))
		return (NULL);
	while(j < i && cmd[j])
	{
		var[j] = cmd[j];
		j++;
	}
	var[j] = '\0';
	return (var);
}

char	*get_value(char *cmd)
{
	int		i;
	char	*value;

	i = 0;
	value = NULL;
	while(cmd[i])
	{
		if (cmd[i] == '=' && cmd[i + 1])
		{
			value = ft_strdup(&cmd[i]);
			return (value);
		}
		i++;
	}
	return (value);
}

char	**change_envp(char **env, char *new_env)
{
	int		size;
	char	**var_env;
	int		i;

	i = -1;
	size = size_matrix(env) + 1;
	var_env = malloc(sizeof (char **) * size + 1);
	if (!var_env)
		return (NULL);
	var_env[size] = NULL;
	while(++i < size - 1)
		var_env[i] = ft_strdup(env[i]);
	var_env[i] = ft_strdup(new_env);
	ft_free(env);
	free(new_env);
	return (var_env);
}

int	size_matrix(char **str)
{
	int	i;

	i = 0;
	while(str[i])
		i++;
	return (i);
}

void	exec_unset(char *cmd, t_env *envp)
{
	int		i;
	int		pos;

	i = 0;
	pos = -1;
	while(envp->env[i])
	{
		if (!ft_strncmp(cmd, envp->env[i], ft_strlen(cmd)))
			pos = i;
		i++;
	}
	if (pos >= 0)
		envp->env = rmv_envp(envp->env, pos);
}

char	**rmv_envp(char **env, int i)
{
	int		j;
	int		pos;
	char	**var_env;

	j = 0;
	pos = 0;
	var_env = ft_calloc(sizeof (char **), size_matrix(env));
	if (!var_env)
		return (NULL);
	while(env[pos])
	{
		if (pos != i)
		{
			var_env[j] = ft_strdup(env[pos]);
			j++;
		}
		pos++;
	}
	ft_free(env);
	return (var_env);
}

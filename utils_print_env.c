#include "minishell.h"

void	print_prompt(char *path)
{
	ft_printf("Minishell@Cheetahs");
	ft_printf(":%s", path);
}

void	print_logout(void)
{
	ft_printf("\nexit\n");
	exit(0);
}

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

char	*get_env(char **envp, char *env)
{
	int		i;
	int		len;
	char	*tmp;

	env = ft_strjoin(env, "=");
	len = ft_strlen(env);
	i = 0;
	while (envp[i] && ft_memcmp(env, envp[i], len))
		i++;
	if (envp[i])
		tmp = envp[i] + len;
	else
		tmp = 0;
	free(env);
	return (tmp);
}

char	**copy_env(char **envp, int adc)
{
	int		len;
	int		i;
	char	**copy;

	len = 0;
	i = 0;
	while (envp[len])
		len++;
	copy = (char **)malloc(sizeof(char *) * (len + adc + 1));
	if (!copy)
		return (NULL);
	while (i++ < len)
		copy[i] = ft_strdup(envp[i]);
	return (copy);
}

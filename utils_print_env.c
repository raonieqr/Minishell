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

// char	**copy_env(t_sh *cmd, int adc)
// {
// 	int		len;
// 	int		i;
// 	char	**copy;

// 	len = 0;
// 	i = 0;
// 	while (envp[len])
// 		len++;
// 	copy = (char **)malloc(sizeof(char *) * (len + adc + 1));
// 	if (!copy)
// 		return (NULL);
// 	while (i++ < len)
// 		copy[i] = ft_strdup(envp[i]);
// 	return (copy);
// }

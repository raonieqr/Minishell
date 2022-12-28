#include "minishell.h"

char    **ft_new_trim(char **cmd)
{
    int    i;
	char	*temp;

    i = 0;
    while (cmd[i])
    {
		temp = NULL;
		if (cmd[i][0] == '\'') 
			temp = ft_strtrim(cmd[i], "\'");
        else if (cmd[i][0] == '\"')
			temp = ft_strtrim(cmd[i], "\"");
		if (temp)
		{
			free(cmd[i]);
			cmd[i] = temp;
		}
        i++;
    }
    return (cmd);
}

void	*check_input(char	*prompt, t_sh	*cmd)
{
	char **a;

	if (!prompt)
	{
		printf("\nError\n");
		return (NULL);
	}
	if (!prompt[0])
		return (NULL);
	a = ft_split(prompt, ' ');
	free(prompt);
	//if (!a)
	//	mini_error()
	if (!a)
		return ("");
	a = ft_new_trim(a);
	expand(a);
	return (cmd);
}





// static int	check_char_and_env(char **str, int i, int keys)
// {
// 	int	len_char;
// 	int	len_env;

// 	len_char = size_not_letter(&*str[i + 1], ':');
// 	len_env = size_env(&*str[i + 1]);
// 	if (len_char < len_env)
// 		return (len_char);
// 	return (len_env + keys);
// }

// static int	changing_env(int i, int keys, char **str, t_sh *cmd)
// {
// 	int		len;
// 	char	*temp;
// 	char	*before;
// 	char	*after;
// 	char	*env;

// 	if (special_checks(*str[i + 1]))
// 		keys = 1;
// 	else
// 		keys = 0;
// 	len = check_char_and_env(&*str, i, keys) + 1;
// 	before = ft_strndup(*str, i);
// 	temp = ft_strndup((&*str[i + 1] + keys), len - 1 - keys * 2);
// 	if (!ft_memcmp(temp, "?", 2))
// 		ft_itoa(cmd->back);
//     else env = 0;
// 	after = ft_strdup(&*str[i + len]);
// 	if (!env)
// 		ft_strdup(get_env(cmd->envp, temp));
// 			free(temp);
// 	len = ft_strlen(env);
// 	temp = ft_strjoin(before, env);
// 	freethree_ptrs(before, *str, env);
// 	*str = ft_strjoin(temp, after);
// 	freetwo_ptrs(temp, after);
// 	return (len);
// }

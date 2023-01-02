#include "minishell.h"

int    check_operator(char *prompt)
{
    int i;

    i = 0;
	if (prompt[i] == '>' || prompt[i] == '<' || prompt[i] == '|')
	{
		if (prompt[i] == '>' && prompt[i + 1] == '>')
			return(2);
		else if (prompt[i] == '<' && prompt[i + 1] == '<')
			return (2);
		else
			return (1);
	}
    return (0);
}

int    check_quote_on(char input)
{
	static int d_quote;
	static int	s_quote;

	if (input == 39 && !s_quote &&!d_quote)
		s_quote++;
	else if (input == 39 && !d_quote)
		s_quote--;
	else if (input == '"' && !s_quote && !d_quote)
		d_quote++;
	else if (input == '"' && !s_quote)
		d_quote--;
    if (s_quote || d_quote)
      return (1);
    return (0);
}

char *return_char(char c)
{
	char *new_word;

	new_word = malloc(2 * sizeof(char));
	if (!new_word)
		return(NULL);
	new_word[0] = c;
	new_word[1] = '\0';
	return (new_word);
}

char	*change_special_char(char *input)
{
	int i;
	char	*temp;

	i = 0;
	while (input[i])
	{
		if (!check_quote_on(input[i]))
		{
			if (check_operator(&input[i]))
			{
				temp = ft_substr(input, 0, i);
				temp = ft_strjoin(temp, " ");
				if (check_operator(&input[i]) == 2)
				{
					temp = ft_strjoin(temp, ft_substr(input, i, 2));
					i++;
				}
				else
					temp = ft_strjoin(temp,return_char(input[i]));
				i++;
				temp = ft_strjoin(temp, " ");
				input = ft_strjoin(temp, &input[i]);
			}
		}
		i++;
	}
	return (input);
}

char    *ft_new_trim(char *cmd)
{
	char	*temp;
 

  temp = NULL;
	if (cmd[0] == '\'') 
		temp = ft_strtrim(cmd, "\'");
	else if (cmd[0] == '\"')
		temp = ft_strtrim(cmd, "\"");
	if (temp)
	{
		free(cmd);
		cmd = temp;
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
	if (check_quote(prompt))
		return (0);
	prompt = change_special_char(prompt);
	a = ft_split(prompt, ' ');
	free(prompt);
	//if (!a)
	//	mini_error()
	if (!a)
		return ("");
	a = expand_dir(a);
	int i = 0;
	expand(a);
	while(a[i])
	{
		printf("cmd : %s\n", a[i]);
		i++;
	}
	//a = ft_new_trim(a);
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

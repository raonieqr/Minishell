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
	t_list	*cmd_node;

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
	prompt = ft_strtrim(prompt, " ");
	a = ft_split(prompt, ' ');
	free(prompt);
	//if (!a)
	//	mini_error()
	if (!a)
		return ("");
	a = expand_dir(a);
	expand(a);
	cmd_node = create_nodes(a);
	while(cmd_node)
	{
		int j = 0;
		printf("INFILE : %d\n", cmd_node->infile);
		printf("OUTFILE : %d\n", cmd_node->outfile);
		printf("CMD : ");
		while (cmd_node->cmd[j])
		{
			printf("%s ", cmd_node->cmd[j]);
			j++;
		}
		cmd_node = cmd_node->next;
	}
	//a = ft_new_trim(a);
	return (cmd);
}

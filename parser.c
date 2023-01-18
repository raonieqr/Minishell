#include "minishell.h"

int	check_operator(char *prompt)
{
	int	i;

	i = 0;
	if (prompt[i] == '>' || prompt[i] == '<' || prompt[i] == '|')
	{
		if (prompt[i] == '>' && prompt[i + 1] == '>')
			return (2);
		else if (prompt[i] == '<' && prompt[i + 1] == '<')
			return (2);
		else
			return (1);
	}
	return (0);
}

int	check_quote_on(char input)
{
	static int	d_quote;
	static int	s_quote;

	if (input == 39 && !s_quote && !d_quote)
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

char	*return_char(char c)
{
	char	*new_word;

	new_word = malloc(2 * sizeof(char));
	if (!new_word)
		return (NULL);
	new_word[0] = c;
	new_word[1] = '\0';
	return (new_word);
}

char	*change_special_char(char *input)
{
	int		i;
	char	*temp;
	char	*temp2;

	i = -1;
	while (input[++i])
	{
		if (!check_quote_on(input[i]) && check_operator(&input[i]))
		{
			temp = ft_substr(input, 0, i);
			temp2 = temp;
			temp = ft_strjoin(temp, " ");
			ft_free(&temp2);
			temp = check_temp(temp, input, &i);
			i++;
			temp2 = temp;
			temp = ft_strjoin(temp, " ");
			ft_free(&temp2);
			temp2 = input;
			input = ft_strjoin(temp, &input[i]);
			freetwo_ptrs(&temp, &temp2);
		}
	}
	return (input);
}

void	*check_input(t_sh *cmd, t_env *new_envp)
{
	char	**split_cmd;
	t_list	*cmd_node;
	char	*temp;

	if (!cmd->prompt[0])
		return (NULL);
	cmd->prompt = change_special_char(cmd->prompt);
	temp = cmd->prompt;
	cmd->prompt = ft_strtrim(cmd->prompt, " ");
	free(temp);
	split_cmd = ft_split(cmd->prompt, ' ');
	free(cmd->prompt);
	free(cmd);
	if (!split_cmd || check_double_pipe(split_cmd))
		return (NULL);
	split_cmd = expand_dir(split_cmd);
	if (expand(&split_cmd, new_envp) < 0)
		return (NULL);
	cmd_node = create_nodes(split_cmd, new_envp);
	if (!cmd_node)
		return (NULL);
	loop_command(cmd_node, new_envp);
	free_split(split_cmd);
	ft_freenode(cmd_node);
	return (NULL);
}

#include "minishell.h"

void loop_command(t_list *cmd_node, t_env *env);

int check_operator(char *prompt)
{
	int i;

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

int check_quote_on(char input)
{
	static int d_quote;
	static int s_quote;

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

char *return_char(char c)
{
	char *new_word;

	new_word = malloc(2 * sizeof(char));
	if (!new_word)
		return (NULL);
	new_word[0] = c;
	new_word[1] = '\0';
	return (new_word);
}

char *change_special_char(char *input)
{
	int i;
	char *temp;
	char *temp2;

	i = 0;
	while (input[i])
	{
		if (!check_quote_on(input[i]))
		{
			if (check_operator(&input[i]))
			{
				temp = ft_substr(input, 0, i);
				temp2 = temp;
				temp = ft_strjoin(temp, " ");
				ft_free(&temp2);
				temp2 = temp;
				if (check_operator(&input[i]) == 2)
				{
					temp = ft_strjoin(temp, ft_substr(input, i, 2));
					i++;
				}
				else
					temp = ft_strjoin(temp, return_char(input[i]));
				ft_free(&temp2);
				i++;
				temp2 = temp;
				temp = ft_strjoin(temp, " ");
				ft_free(&temp2);
				input = ft_strjoin(temp, &input[i]);
				ft_free(&temp);
			}
		}
		i++;
	}
	return (input);
}

char *ft_new_trim(char *cmd)
{
	char *temp;

	temp = NULL;
	if (cmd[0] == '\'')
		temp = ft_strtrim(cmd, "\'");
	else if (cmd[0] == '\"')
		temp = ft_strtrim(cmd, "\"");
	else
		temp = ft_strdup(cmd);
	if (temp)
	{
		free(cmd);
		cmd = temp;
	}
	return (cmd);
}

int check_double_pipe(char **cmds)
{
	int i;

	i = 0;
	while (cmds[i])
	{
		if (cmds[i + 1])
		{
			if (cmds[i][0] == '|' && cmds[i + 1][0] == '|')
			{
				printf("minishell: syntax error near unexpected token `|'\n");
				return (1);
			}
		}
		i++;
	}
	return (0);
}

void *check_input(t_sh *cmd, t_env *new_envp)
{
	char **a;
	t_list *cmd_node;

	if (!cmd->prompt)
	{
		printf("\nError\n");
		return (NULL);
	}
	if (!cmd->prompt[0])
		return (NULL);
	if (check_quote(cmd->prompt))
	{
		printf("Unclosed quotes\n");
		return (0);
	}
	// cmd->prompt = change_char(cmd->prompt);
	cmd->prompt = change_special_char(cmd->prompt);
	cmd->prompt = ft_strtrim(cmd->prompt, " ");
	a = ft_split(cmd->prompt, ' ');
	free(cmd->prompt);
	if (!a)
		return ("error");
	if (check_double_pipe(a))
		return (NULL);
	a = expand_dir(a);
	if (expand(a, new_envp) < 0)
	{
		printf("\n");
		return (NULL);
	}
	cmd_node = create_nodes(a, new_envp);
	loop_command(cmd_node, new_envp);
	return (NULL);
}

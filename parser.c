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

void ft_freenode(t_list *cmd)
{
	t_list *temp;
	t_list *aux;
	int i;

	temp = cmd;
	while (temp)
	{
		aux = temp;
		i = -1;
		if (aux->cmd_path)
			free(aux->cmd_path);
		while (aux->cmd[++i])
			free(aux->cmd[i]);
		if (aux->cmd)
			free(aux->cmd);
		if (aux->infile > 2)
			close(aux->infile);
		if (aux->outfile > 2)
			close(aux->outfile);
		temp = temp->next;
		free(aux);
	}
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

char *check_temp(char *temp, char *input, int i)
{
	char *temp2;
	char *aux;

	temp2 = temp;
	if (check_operator(&input[i]) == 2)
	{
		aux = ft_substr(input, i, 2);
		temp = ft_strjoin(temp, aux);
		i++;
	}
	else
	{
		aux = return_char(input[i]);
		temp = ft_strjoin(temp, aux);
	}
	freetwo_ptrs(&temp2, &aux);
	return (temp);
}

char *change_special_char(char *input)
{
	int i;
	char *temp;
	char *temp2;

	i = 0;
	while (input[i++])
	{
		if (!check_quote_on(input[i]))
		{
			if (check_operator(&input[i]))
			{
				temp = ft_substr(input, 0, i);
				temp2 = temp;
				temp = ft_strjoin(temp, " ");
				ft_free(&temp2);
				temp = check_temp(temp, input, i);
				i++;
				temp2 = temp;
				temp = ft_strjoin(temp, " ");
				ft_free(&temp2);
				temp2 = input;
				input = ft_strjoin(temp, &input[i]);
				ft_free(&temp);
				ft_free(&temp2);
			}
		}
	}
	return (input);
}

char *ft_new_trim(char *cmd)
{
	char *temp;

	temp = NULL;
	if (cmd[0] == '\'' || cmd[ft_strlen(cmd) - 1] == '\'')
		temp = ft_strtrim(cmd, "\'");
	else if (cmd[0] == '\"' || cmd[ft_strlen(cmd) - 1] == '\"')
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
	char **split_cmd;
	t_list *cmd_node;
	char *temp;

	split_cmd = NULL;
	if (!cmd->prompt[0])
		return (NULL);
	cmd->prompt = change_special_char(cmd->prompt);
	temp = cmd->prompt;
	cmd->prompt = ft_strtrim(cmd->prompt, " ");
	free(temp);
	split_cmd = ft_split(cmd->prompt, ' ');
	free(cmd->prompt);
	if (!split_cmd)
		return (NULL);
	if (check_double_pipe(split_cmd))
		return (NULL);
	split_cmd = expand_dir(split_cmd);
	expand(split_cmd, new_envp);
	// printf("%s\n", split_cmd[0]);
	cmd_node = create_nodes(split_cmd, new_envp);
	if (!cmd_node)
		return (NULL);
	loop_command(cmd_node, new_envp);
	ft_freenode(cmd_node);
	// free(cmd);
	free_split(&split_cmd);
	return (NULL);
}

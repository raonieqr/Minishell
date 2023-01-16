#include "minishell.h"

void	print_start(void)
{
	printf("%s", LINE_1);
	printf("%s", LINE_2);
	printf("%s", LINE_3);
	printf("%s", LINE_4);
	printf("%s", LINE_5);
}

char	*return_path(void)
{
	char	*home;
	char	cwd[4098];
	char	*path;

	home = getenv("HOME");
	getcwd(cwd, 4097);
	if (ft_memcmp(home, cwd, ft_strlen(home)))
		path = ft_strdup(cwd);
	else
		path = ft_strjoin("~", cwd + ft_strlen(home));
	return (path);
}

void	ft_free(char **str)
{
	if (*str)
	{
		free(*str);
		*str = NULL;
	}
}

void	print_prompt(t_sh *cmd)
{
	cmd->envp = return_path();
	cmd->temp = cmd->envp;
	cmd->envp = ft_strjoin(cmd->envp, "$ ");
	ft_free(&cmd->temp);
	cmd->temp = ft_strjoin("\033[0;32mMinishell@42rio:\033[0:39m", cmd->envp);
	ft_free(&cmd->envp);
	cmd->prompt = readline(cmd->temp);
	if (cmd->prompt)
		add_history(cmd->prompt);
	ft_free(&cmd->temp);
}

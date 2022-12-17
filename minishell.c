#include "minishell.h"

static void init(t_sh *cmd, char **argv, char **envp)
{
	cmd = malloc (sizeof(t_sh));
	cmd->envp = copy_env(envp, 0);
	cmd->exp = ft_calloc(sizeof(char *), 1);
	cmd->argv = argv;
	cmd->finish = 1;
	cmd->str = 0;
	cmd->children = 0;
	cmd->back = 0;
	signal(SIGQUIT, handle_sig);
}

static void prompt(char **envp)
{
	char *home;
	char *path;
	char cwd[1001];
	int len;

	home = get_env(envp, "HOME");
	len = ft_strlen(home);
	getcwd(cwd, 1000);
	if (ft_memcmp(cwd, home, len))
		path = ft_strdup(cwd);
	else
		path = ft_strjoin("~", cwd + len);
	print_prompt(path);
	free(path);
}

void handle_sig(int sig)
{
	char cwd[1001];

	if (sig == SIGINT)
	{
		getcwd(cwd, 1000);

	}
}

int main(int argc, char **argv, char **envp)
{
	t_sh *cmd;
	int	res;
	int res2;
	char letter;

	res = 1;
	cmd = NULL;
	//criar uma função e por dentro do argc
	if (argc == 1)
	{
		init(cmd, argv, envp);
		while (cmd->finish)
		{
			if (res)
				prompt(cmd->envp);
			signal(SIGINT, handle_sig);
			while ((res = read(1, &letter, 1)) && letter != 10)
				char_copy(&cmd->str, letter);
			res2 = ft_strlen(cmd->str);
			if (letter == 10)
				set_command(cmd);
			if (!res && !res2)
				print_logout();
		}
	}
	else
		return (res);
}

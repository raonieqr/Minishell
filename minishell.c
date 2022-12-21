#include "minishell.h"

char *return_path(void)
{
	char	*home;
	char	cwd[4098];
	char	*path;

	home = getenv("HOME");
	getcwd(cwd, 4097);
	if (ft_memcmp(home, cwd, ft_strlen(home)))
		path = ft_strdup(home);
	else
		path = ft_strjoin("~", cwd + ft_strlen(home));
	return (path);
}

static void	init(t_sh *cmd)
{
	cmd = malloc(sizeof(t_sh));
	cmd->envp = NULL;
	cmd->exp = ft_calloc(sizeof(char *), 1);
	cmd->finish = 1;
	cmd->str = 0;
	cmd->children = 0;
	cmd->back = 0;
	signal(SIGQUIT, print_prompt);
}

void	print_jump(void)
{
	char *prompt;
	char *temp;
	char	*envp;

	//ft_putstr_fd("\033[2D\033[0K", 2);
	
	printf("\n");
	envp = return_path();
	envp = ft_strjoin(envp, "$ ");
	temp = ft_strjoin("Minishell@ubuntu:", envp);
	prompt = readline(temp);
	freetwo_ptrs(envp, temp);
	signal(SIGQUIT, print_prompt);
	(void)prompt;
	if (temp && *temp)
		add_history (temp);
}

void	handle_sig(int sig)
{

	if (sig == SIGINT)
	{
		// char *prompt;
		// char *temp;
		printf("\n");
		// envp = return_path();
		// envp = ft_strjoin(envp, "$ ");
		// temp = ft_strjoin("Minishell@ubuntu:", envp);
		// printf("%s", temp);
		// freetwo_ptrs(envp, temp);
		// (void)prompt;
		// if (temp && *temp)
		// 	add_history (temp);
	}
	else if (sig == SIGTSTP)
		print_logout();
	else if (sig == SIGQUIT)
		signal(SIGQUIT, SIG_IGN);	

}

int	main(int argc, char **argv)
{
	t_sh	cmd;
	struct sigaction	act;
	// char cwd[1001];
	int		res;
	int		res2;
	// char	letter;

	act.sa_sigaction = (void *)handle_sig;
	act.sa_flags = SA_SIGINFO;
	sigaction (SIGQUIT, &act, NULL);
	sigaction (SIGINT, &act, NULL);
	sigaction (SIGTSTP, &act, NULL);
	res = 1;
	res2 = 1;
	// int argc = 1;
	// signal(SIGQUIT, handle_sig);
	signal(SIGQUIT, SIG_IGN);	
	(void)argv;
	if (argc == 1)
	{
		init(&cmd);
		while (1)
		{
			//signal(SIGQUIT, SIG_IGN);	
			if (res)
				print_prompt(&cmd);	
			//signal(SIGQUIT, SIG_IGN);	
			//signal(SIGINT, handle_sig);
			// signal(SIGINT, handle_sig);
			// while ((res = read(1, &letter, 1)) && letter != 10)
			// 	char_copy(&cmd->str, letter);
			// res2 = ft_strlen(cmd->str);
			// if (letter == 10)
			// 	// set_command(cmd);
			if (!res && !res2)
				print_logout();
		}
	}
	else
		return (res);
}

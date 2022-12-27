#include "minishell.h"

void	print_start(void)
{
	printf(",--.   ,--.,--.        ,--.       ,--.            ,--.,--. \n");
	printf("|   `.'   |`--',--,--, `--' ,---. |  ,---.  ,---. |  ||  | \n");
	printf("|  |'.'|  |,--.|      |,--.(  .-' |  .-.  || .-. :|  ||  | \n");
	printf("|  |   |  ||  ||  ||  ||  |.-'  `)|  | |  ||   --.|  ||  | \n");
	printf("`--'   `--'`--'`--''--'`--'`----' `--' `--' `----'`--'`--' \n");
}

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

static t_sh	*init(void)
{
	t_sh *cmd;
	cmd = malloc(sizeof(t_sh));
	cmd->envp = NULL;
	cmd->exp = ft_calloc(sizeof(char *), 1);
	cmd->finish = 1;
	cmd->str = 0;
	cmd->children = 0;
	cmd->back = 0;
	return (cmd);
}

void	handle_sig(int sig, siginfo_t *info, void *algo)
{

	(void) algo;
	(void) *info;
	if (sig == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	else if (sig == SIGTSTP)
		print_logout();
	else if (sig == SIGQUIT)
		signal(SIGQUIT, SIG_IGN);	
}

void	signals(void)
{
	struct sigaction	act;

	act.sa_sigaction = (void *)handle_sig;
	act.sa_flags = SA_SIGINFO;
	sigaction (SIGQUIT, &act, NULL);
	sigaction (SIGINT, &act, NULL);
	sigaction (SIGTSTP, &act, NULL);
}

int	main(int argc, char **argv)
{
	t_sh	*cmd;
	// char cwd[1001];
	int		res;
	int		res2;
	// char	letter;

	res = 1;
	res2 = 1;
	print_start();
	// int argc = 1;
	signals();
	(void)argv;
	if (argc == 1)
	{
		cmd = init();
		while (cmd->finish)
		{
			if (res)
				print_prompt(cmd);	
			// while ((res = read(1, &letter, 1)) && letter != 10)
			// 	char_copy(&cmd->str, letter);
			// res2 = ft_strlen(cmd->str);
			// if (letter == 10)
			// 	// set_command(cmd);
			check_input(cmd->prompt, cmd);
			if (!res && !res2)
				print_logout();
		}
	}
	else
		return (res);
}
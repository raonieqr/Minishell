#include "minishell.h"

static t_sh	*init(void)
{
	t_sh	*cmd;

	cmd = malloc(sizeof(t_sh));
	cmd->envp = NULL;
	cmd->exp = ft_calloc(sizeof(char *), 1);
	cmd->str = 0;
	cmd->back = 0;
	return (cmd);
}

void	handle_sig(int sig, siginfo_t *info, void *algo)
{
	(void)algo;
	(void)*info;
	if (sig == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	else if (sig == SIGQUIT)
		signal(SIGQUIT, SIG_IGN);
}

void	signals(void)
{
	struct sigaction	act;

	act.sa_sigaction = (void *)handle_sig;
	act.sa_flags = SA_SIGINFO;
	sigaction(SIGQUIT, &act, NULL);
	sigaction(SIGINT, &act, NULL);
}


int	check_pipe(t_sh *cmd)
{
	int i;

	i = 0;
	while (cmd->prompt[i])
	{
		if (cmd->prompt[i] == '\\')
		{
			while (cmd->prompt[i + 1])
			{
				if (ft_isspace(cmd->prompt[i + 1])
					
				i++;
			}

		}
		i++;
	}


}

int validate_prompt(t_sh	*cmd)
{
	if (check_quote(cmd->prompt))
		return (0);
	if (check_pipe(cmd->prompt))
		return (0);


}

//int main(void)
int	main(int argc, char **argv)
{
	t_sh	*cmd;

	print_start();
	signals();
	(void)argv;
	if (argc == 1)
	{
		cmd = init();
		while (1)
		{
			print_prompt(cmd);
			if (!cmd->prompt)
			{
				printf("Exit\n");
				exit(0);
			}
			if (validate_prompt(cmd))
				check_input(cmd->prompt);
		}
	}
	return (0);
}

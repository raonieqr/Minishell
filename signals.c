#include "minishell.h"

void	child_signals(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

void	handle_sig(int sig, siginfo_t *info, void *algo)
{
	(void)algo;
	(void)*info;
	if (sig == SIGINT)
	{
		g_status = 130;
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	signals(void)
{
	struct sigaction	act;

	act.sa_sigaction = (void *)handle_sig;
	act.sa_flags = SA_SIGINFO;
	signal(SIGQUIT, SIG_IGN);
	sigaction(SIGINT, &act, NULL);
}

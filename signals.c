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
		if (RL_ISSTATE(RL_STATE_READCMD))
			ioctl(STDIN_FILENO, TIOCSTI, "\n");
		else
			write(1, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
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

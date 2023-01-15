#include "minishell.h"

int g_status;

static t_sh	*init(void)
{
	t_sh	*cmd;

	cmd = malloc(sizeof(t_sh));
	cmd->envp = NULL;
	//cmd->exp = ft_calloc(sizeof(char *), 1);
	cmd->str = 0;
	return (cmd);
}

/*TROCAR ISSO*/

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

int	check_pipe(t_sh *cmd)
{
	char *tmp;

	tmp = ft_strtrim(cmd->prompt, " ");
	if (tmp[0] == '|' || tmp[ft_strlen(tmp) - 1] == '|')
	{
		ft_perror(2, NULL, PIPE);
		ft_free(&tmp);
		return (1);
	}
	ft_free(&tmp);
	return (0);
}

int validate_prompt(t_sh	*cmd)
{
	if (!cmd->prompt)
	{
		printf("\nError\n");
		return (0);
	}
	if (check_quote(cmd->prompt))
	{
		ft_free(&cmd->prompt);
		ft_perror(2, NULL, QUOTES);
		return (0);
	}
	if (check_pipe(cmd))
	{
		ft_free(&cmd->prompt);
		return (0);
	}
	return (1);
}

//int main(void)
int	main(int argc, char **argv, char **envp)
{
	t_sh	*cmd;
	t_env	*new_envp;

	//print_start();
	(void)argv;
	if (argc == 1)
	{	
		new_envp = malloc(sizeof (t_env));
		new_envp->env = copy_env(envp);
		cmd = init();
		while (1)
		{
			signals();
			print_prompt(cmd);
			if (!cmd->prompt)
			{
				free_split(&new_envp->env);
				printf("\n");
				exit(0);
			}
			if (validate_prompt(cmd))
				check_input(cmd, new_envp);
		}
	}
	return (0);
}

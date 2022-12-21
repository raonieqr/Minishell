#include "minishell.h"

// static void	init(t_sh *cmd)
// {
// 	cmd = malloc(sizeof(t_sh));
// 	cmd->envp = NULL;
// 	cmd->exp = ft_calloc(sizeof(char *), 1);
// 	cmd->finish = 1;
// 	cmd->str = 0;
// 	cmd->children = 0;
// 	cmd->back = 0;
// 	// signal(SIGQUIT, handle_sig);
// }

void	handle_sig(int sig)
{
	char	cwd[1001];

	if (sig == SIGINT)
	{
		getcwd(cwd, 1000);
	}
}

int	main(int argc, char **argv)
{
	t_sh	cmd;
	// char cwd[1001];
	int		res;
	int		res2;
	// char	letter;

	res = 1;
	// int argc = 1;
	(void)argv;
	if (argc == 1)
	{
		// init(cmd);
		while (1)
		{
			if (res)
			{
				print_prompt(&cmd);	
			}
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

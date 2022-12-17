#ifndef MINISHELL_H
# define MINISHELL_H

# include "./ft_printf/ft_printf.h"
# include <dirent.h>
# include <errno.h>
# include <fcntl.h>
# include <signal.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/wait.h>

typedef struct s_cmd
{
	char	**envp;
	char	**exp;
	char	**cmd;
	char	**argv;
	char	*str;
	int		back;
	int		argc;
	int		finish;
	int		children;
}			t_sh;

void		print_prompt(char *path);
void		print_logout(void);
char		*get_env(char **envp, char *env);
char		**copy_env(char **envp, int adc);
void		char_copy(char **str, char c);
void		handle_sig(int sig);
#endif

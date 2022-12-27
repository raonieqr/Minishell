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
# include <readline/readline.h>
# include <readline/history.h>

typedef struct s_cmd
{
	char	*envp;
	char	**exp;
	char	**cmd;
	char	**argv;
	char	*str;
	char 	*prompt;
	char 	*temp;
	int		back;
	int		argc;
	int		finish;
	int		children;
}			t_sh;

void		print_prompt();
void	*check_input(char	*prompt, t_sh	*cmd);
void		print_logout(void);
void		handle_sig(int sig, siginfo_t *info, void *algo);
int	size_not_letter(char *str, char c);
int	size_env(char *str);
int	special_checks(char c);
void	char_copy(char **str, char c);
// char	**copy_env(char *envp, int adc);
void	freethree_ptrs(char *s, char *s2, char *s3);
void	freetwo_ptrs(char *s, char *s2);
void	print_jump(void);
char 	*return_path(void);
#endif

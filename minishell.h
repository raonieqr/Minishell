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


void	print_prompt();
void	rl_replace_line (const char *text, int clear_undo);
void	*check_input(char	*prompt, t_sh	*cmd);
void	print_logout(void);
void	handle_sig(int sig, siginfo_t *info, void *algo);
int		size_not_letter(char *str, char c);
int		size_env(char *str);
int		special_checks(char c);
void	char_copy(char **str, char c);
// char	**copy_env(char *envp, int adc);
void	freethree_ptrs(char *s, char *s2, char *s3);
void	freetwo_ptrs(char *s, char *s2);
void	print_jump(void);
char 	*return_path(void);
void	expand(char **cmds);
char	**expand_dir(char **cmds);
int 	is_quote(char *str);
int   check_quote(char *input);
char	*change_var(char *cmd, char *var, char *value, int pos_s);
char  *ft_new_trim(char *cmd);
int    check_operator(char *prompt);
t_list *create_nodes(char **args);

int	ft_get_outfile(t_list* node, char **args, int i);
int ft_get_outfile2(t_list* node, char **args, int i);
int ft_get_infile2(t_list* node, char **args, int i);
int ft_get_infile(t_list* node, char **args, int i);
char 	*get_input(char *delimiter);
#endif

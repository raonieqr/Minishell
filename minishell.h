#ifndef MINISHELL_H
#define MINISHELL_H

#include "./ft_printf/ft_printf.h"
#include <dirent.h>
#include <errno.h>
#include <fcntl.h>
#include <readline/history.h>
#include <readline/readline.h>
#include <signal.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/ioctl.h>
#include <termios.h>

#define HDOC_WARN "minishell: warning: here-document delimited by end-of-file"

typedef struct s_cmd
{
	char *envp;
	char **exp;
	char **cmd;
	char **argv;
	char *str;
	char *prompt;
	char *temp;
	struct s_list *list;
} t_sh;

extern int g_status;

enum e_error
{
	NDIR = 1,
	PIPERR = 4,
	MALLOC_ERR = 5,
	SYNTAX = 6,
	QUOTES = 7,
	PIPE = 8,
};

#define line_1 "\033[0;31m,--.   ,--.,--.        ,--.       ,--.            ,--.,--.\033[0:39m\n"
#define line_2 "\033[0;33m|   `.'   |`--',--,--, `--' ,---. |  ,---.  ,---. |  ||  | \033[0:39m\n"
#define line_3 "\033[0;32m|  |'.'|  |,--.|      |,--.(  .-' |  .-.  || .-. :|  ||  | \033[0:39m\n"
#define line_4 "\033[0;34m|  |   |  ||  ||  ||  ||  |.-'  `)|  | |  ||   --.|  ||  | \033[0:39m\n"
#define line_5 "\033[0;35m`--'   `--'`--'`--''--'`--'`----' `--' `--' `----'`--'`--' \033[0:39m\n"

void print_start(void);
void print_prompt(t_sh *cmd);
void *check_input(t_sh *cmd, t_env *new_envp);
void ft_free(char **str);

void rl_replace_line(const char *text, int clear_undo);
void handle_sig(int sig, siginfo_t *info, void *algo);

void freethree_ptrs(char **s, char **s2, char **s3);
void freetwo_ptrs(char **s, char **s2);
int expand(char **cmds, t_env *new_envp);
char **expand_dir(char **cmds);
int is_quote(char *str);
int check_quote(char *input);
char *change_var(char *cmd, char *var, char *value, int pos_s);
char *ft_new_trim(char *cmd);
int check_operator(char *prompt);
t_list *create_nodes(char **args, t_env *new_envp);
int here_docs(char *delimiter);
int ft_get_outfile(t_list *node, char **args, int i);
int ft_get_outfile2(t_list *node, char **args, int i);
int ft_get_infile2(t_list *node, char **args, int i);
int ft_get_infile(t_list *node, char **args, int i);
char *get_input(char *delimiter);
int is_builtin(char **cmd);
char *to_lower(char *cmd);
int exec_echo(char **cmd);
int exec_cd(t_list *cmds);
int exec_pwd(void);
int get_path(t_list *cmds);
char *test_path(char **cmd);
int check_builtin(t_list *cmds);
int exec_builtin(t_list *cmds, t_env *envp);
void execute_cmds(t_list *cmds);
int execution(t_list *cmds);
char *test_access(char **path, char **cmd);
void *verify_fork(t_list *cmds, int *fd);
int get_status(t_list *cmd_node);
int check_exec(t_list *list);
void loop_command(t_list *cmd_node, t_env *new_cmd);
int ft_isspace(char c);
char *change_special_char(char *input);
char **change_envp(char **env, char *new_env);
int size_matrix(char **str);
char *get_value(char *cmd);
int ft_ismetachar(char c);
char *get_var(char *cmd);
int exec_exports(char *cmd, t_env *envp);
char **rmv_envp(char **env, int i);
void exec_unset(char *cmds, t_env *envp);
void exit_error(char *str);
char *ft_get_env(char **envp, char *var);
// char *change_char(char *prompt);
int ft_perror(int status, char *cmd, int code);
int has_output(char *cmd);
void free_split(char ***splited);
int check_pipe(t_sh *cmd);
void exec_env(t_env *envp);
char    *cmd_prompt(char *input);
void	ft_freenode(t_list *cmd);
char	*check_temp(char *temp, char *input, int i);
int	check_double_pipe(char **cmds);
char	*return_char(char c);
void	signals(void);
void	child_signals(void);

#endif

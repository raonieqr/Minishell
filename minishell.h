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

typedef struct s_cmd
{
	char *envp;
	char **exp;
	char **cmd;
	char **argv;
	char *str;
	char *prompt;
	char *temp;
	int back;
	int argc;
} t_sh;

void print_start(void);
void print_prompt(t_sh *cmd);
void *check_input(char *prompt);
void ft_free(char **str);

void rl_replace_line(const char *text, int clear_undo);
void handle_sig(int sig, siginfo_t *info, void *algo);
int size_not_letter(char *str, char c);
int size_env(char *str);
void char_copy(char **str, char c);
// char	**copy_env(char *envp, int adc);
void freethree_ptrs(char *s, char *s2, char *s3);
void freetwo_ptrs(char *s, char *s2);
int expand(char **cmds);
char **expand_dir(char **cmds);
int is_quote(char *str);
int check_quote(char *input);
char *change_var(char *cmd, char *var, char *value, int pos_s);
char *ft_new_trim(char *cmd);
int check_operator(char *prompt);
t_list *create_nodes(char **args);
int here_docs(char *delimiter);
int ft_get_outfile(t_list *node, char **args, int i);
int ft_get_outfile2(t_list *node, char **args, int i);
int ft_get_infile2(t_list *node, char **args, int i);
int ft_get_infile(t_list *node, char **args, int i);
int special_checks(char c);
char *get_input(char *delimiter);
int is_builtin(char **cmd);
char *to_lower(char *cmd);
void exec_echo(char **cmd);
void exec_cd(char **cmd);
void exec_pwd(void);
void get_path(t_list *cmds);
char *test_path(char **cmd);
int check_builtin_system(t_list *cmds);
int exec_builtin(t_list *cmds);
void execute_cmds(t_list *cmds);
int execution(t_list *cmds);
char *test_access(char **path, char **cmd);
void *verify_fork(t_list *cmds, int *fd);
int get_status(t_list *cmd_node);
int check_exec(t_list *list);
void loop_command(t_list *cmd_node);
int ft_isspace(char c);
char *change_special_char(char *input);
// char *change_char(char *prompt);

#endif

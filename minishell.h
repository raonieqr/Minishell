#ifndef MINISHELL_H
# define MINISHELL_H

# include "./ft_printf/ft_printf.h"
# include <fcntl.h>
# include <dirent.h>
# include <signal.h>
# include <errno.h>
# include <string.h>
# include <sys/wait.h>
# include <sys/stat.h>

typedef struct s_cmd
{
    char **envp;
    char **exp;
    char **cmd;
    char **argv;
    char *str;
    int back;
    int argc;
    int finish;
    int children;
} t_sh;

void print_prompt(char *path);
void print_logout();
char	*get_env(char **envp, char *env);
char	**copy_env(char **envp, int adc);
void char_copy(char **str, char c);
#endif

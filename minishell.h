#ifndef MINISHELL_H
# define MINISHELL_H

# include "./ft_printf/ft_printf.h"
# include <dirent.h>
# include <errno.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <string.h>
# include <sys/ioctl.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <termios.h>

# define HDOC_WARN "minishell: warning: here-document delimited by end-of-file"

typedef struct s_cmd
{
	char			*envp;
	char			*prompt;
	char			*temp;
	struct s_list	*list;
}					t_sh;

extern int			g_status;

enum				e_error
{
	PIPERR = 4,
	MALLOC_ERR = 5,
	SYNTAX = 6,
	QUOTES = 7,
	PIPE = 8,
};

# define LINE_1 "\033[0;31m,--.   ,--.,--.        ,--.       ,--.            ,\
--.,--.\033[0:39m\n"
# define LINE_2 "\033[0;33m|   `.'   |`--',--,--, `--' ,---. |  ,---.  ,---. |\
  ||  | \033[0:39m\n"
# define LINE_3 "\033[0;32m|  |'.'|  |,--.|      |,--.(  .-' |  .-.  || .-. :|\
  ||  | \033[0:39m\n"
# define LINE_4 "\033[0;34m|  |   |  ||  ||  ||  ||  |.-'  `)|  | |  ||   --.|\
  ||  | \033[0:39m\n"
# define LINE_5 "\033[0;35m`--'   `--'`--'`--''--'`--'`----' `--' `--' `----'`\
--'`--' \033[0:39m\n"

// MINISHELL
t_sh				*init(void);
int					validate_prompt(t_sh *cmd);
void				close_prompt(t_env *new_envp, t_sh *cmd);
int					main(int argc, char **argv, char **envp);

// BUILTIN
int					check_builtin(t_list *cmds);
int					is_builtin(char **cmd);
int					exec_builtin(t_list *cmds, t_env *envp);

// CMD_BUILTINS
void				print_break_line(char **cmd);
int					exec_echo(char **cmd);
int					exec_cd(t_list *cmds, t_env *envp);
int					exec_pwd(void);
void				exec_env(t_env *envp);

// CONFIG_CMD
t_list				*cmd_init(void);
int					check_for_cmd(char **input, int i);
int					cmd_len(char **n_cmd, int i);
char				**ft_add_cmd(char **n_cmd, char *args);

// COPY_ENVP
char				**copy_env(char **envp);
char				**change_envp(char **env, char *new_env);
char				**rmv_envp(char **env, int i);

// EXEC_CMD
int					check_exec(t_list *list);
void				check_commands(t_list *list);
void				error_fork(t_list *cmd_node);
void				loop_command(t_list *cmd_node, t_env *envp);

// EXECUTION
int					matrix_len(char **matrix);
char				*test_path(t_list *cmd);
char				*test_access(char **path, char **cmd);
DIR					*check_cmd(t_list *cmds);
int					get_path(t_list *cmds);

// EXPAND_VAR
int					get_flag(char ***tmp, int *i, int *j, t_env *new_env);
int					return_cmds(char ***cmds, char **tmp, char *to_free, int i);
int					not_env(char ***cmds, int i, int j, t_env *new_envp);
char				**rmv_str(char **str, int pos);
char				*rmv_var(int start, int end, char *str);

// EXPANSIONS_DIR
int					is_quote(char *str);
int					expand_var(char ***cmds, int i, int j, t_env *new_envp);
char				**expand_dir(char **cmds);
void				set_oldpwd(t_env *envp);

// EXPANSIONS
char				*change_var(char *cmd, char *var, char *value, int pos_s);
char				*get_sub(char *str);
char				*join_three(char *str, int j, char *str2, t_env *new_envp);
char				*join_status(char *str, int j, char *str2);
int					expand(char ***cmds, t_env *new_envp);

// FREEDOM_SINGS
void				free_split(char **splited);
void				free_stack(t_list **stack);
void				ft_freenode(t_list *cmd);
void				freethree_ptrs(char **s, char **s2, char **s3);
void				freetwo_ptrs(char **s, char **s2);

// GET_FILES
int					open_file(char *path, int cur_fd, int c_write,
						int c_append);
int					ft_get_outfile(t_list *node, char **args, int i);
int					ft_get_outfile2(t_list *node, char **args, int i);
int					ft_get_infile2(t_list *node, char **args, int i);
int					ft_get_infile(t_list *node, char **args, int i);

// HERE_DOCS
int					check_end(char *input, char *delimiter);
char				*get_input(char *delimiter);
int					here_docs(char *delimiter);
char				*return_free(char *input);

// NODES
int					complement_fill_node(t_list *node, char **args, int i);
int					fill_node(t_list *node, char **args, int i);
void				ft_add_node(t_list **lst);
int					verifying_fill_node(t_list *cmds, int check);
t_list				*create_nodes(char **args, t_env *new_envp);

// PARSER_2
char				*ft_new_trim(char *cmd);
char				*check_temp(char *temp, char *input, int *i);
int					return_swap(char ****cmds, char **tmp);
void				exec_exit(t_list *cmds, t_env *envp);
int					check_redir(char *prompt);

// PARSER
int					check_operator(char *prompt);
int					check_quote_on(char input);
char				*return_char(char c);
char				*change_special_char(char *input);
void				*check_input(t_sh *cmd, t_env *new_envp);

//PIPE
void				childs_pipe(int *flags, int *fd, t_list *list);
void				change_pipe(int *fd);
int					see_pipe(int *fd, t_list *list);
int					check_command_pipe(t_list *list);
int					check_double_pipe(char **cmds);

// PROMPT
void				print_start(void);
char				*return_path(void);
void				ft_free(char **str);
void				print_prompt(t_sh *cmd);
void				freetwo_voids(t_sh *s, t_env *s2);

// SIGNALS
void				child_signals(void);
void				handle_sig(int sig, siginfo_t *info, void *algo);
void				signals(void);

// UTILS_CHECKERS
int					ft_isspace(char c);
int					ft_ismetachar(char c);
int					has_output(char *cmd);
int					check_pipe(t_sh *cmd);
int					check_quote(char *input);

// UTILS_LEN
void				check_status(int code);
int					ft_perror(int status, char *cmd, int code);
int					size_matrix(char **str);
int					ft_len_char(char *str);
char				*to_lower(char *cmd);

// UTILS_NODES
t_list				*second_last_node(t_list *list);
void				*change_node(t_list *list);
void				*node_change(t_list *list, t_list *temp);
t_list				*return_node(t_list *list, int check, char **args);
void				close_free(t_list *cur);

// UTILS_PRINT_ENV
int					exec_exports(char *cmd, t_env *envp);
char				*ft_get_env(char **envp, char *var);
char				*get_var(char *cmd);
char				*get_value(char *cmd);
void				exec_unset(char *cmd, t_env *envp);

#endif

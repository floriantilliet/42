/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftilliet <ftilliet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 05:43:39 by ftilliet          #+#    #+#             */
/*   Updated: 2024/09/12 11:11:14 by ftilliet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <errno.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <unistd.h>

# define CMD 0
# define ARG 1
# define PIPE 2
# define OUT 3
# define IN 4
# define APPEND 5
# define HEREDOC 6
# define IS_SPACE 7

typedef enum e_flag_sig
{
	PROMPT,
	HERE_DOC,
	CHILD
}					t_flag_sig;

# define FALSE 0
# define TRUE 1
# define STDERR STDERR_FILENO
# define ERR_PIPE "minishell: syntax error near unexpected token `|'\n"
# define ERR_REDIR "minishell: syntax error near unexpected token `newline'\n"
# define ERR_REDIRECT_2 "minishell: syntax error near unexpected token\n"
# define ERROR_OPEN "Couldn't open the file\n"
# define ERROR_PIPE "Some mistakes occures when using pipe\n"
# define ERR_CMD "minishell: %s: command not found\n"
# define ERR_IS_DIR "minishell: %s: Is a directory\n"
# define ERROR_DUP "Some mistakes occures when using dup\n"
# define ERROR_FORK "Some mistakes occures when using fork\n"
# define ERROR_EXEC "Some mistakes occures when using execve\n"
# define ERR_MALLOC "Error malloc\n"
# define ERR_EXPORT "minishell: export: `%s': not a valid identifier\n"
# define ERR_CD_NO_ARGS "minishell: cd: HOME not set\n"
# define ERR_CD "minishell: cd: %s: No such file or directory\n"
# define ERR_CD_NB_ARG "minishell: cd: too many arguments\n"
# define ERR_ENV "env: ‘%s’: No such file or directory\n"
# define ERR_EXIT_NB_ARG "minishell: exit: too many arguments\n"
# define ERR_EXIT_WRONG_ARG "minishell: exit: %s: numeric argument required\n"
# define ERROR_PERMISSION "minishell: %s: Permission denied\n"
# define ERR_NOT_FOUND "minishell: %s: File not found\n"
# define ERR_COMP_DIR "Error: A component of the path %s is not a directory\n"
# define ERR_ACCESS "Error: Cannot access %s: %s\n"
# define ERR_PERM "minishell: %s: Permission denied\n"
# define ERR_EXIST "minishell: %s: No such file or directory\n"

extern int			g_exit_code;

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
	struct s_env	*prev;
	int				fd_in;
	int				fd_out;
	unsigned char	exit_code;
}					t_env;

typedef struct s_token
{
	char			*value;
	char			*file_n;
	int				type;
	int				if_pipe;
	int				fd;
	int				fd_pipe[2];
	struct s_token	*next;
	struct s_token	*prev;
	struct s_token	*head;
}					t_token;

typedef struct s_cmd
{
	char			*path;
	int				free_path;
	int				len;
	char			**cmd;
	char			**env;
	int				is_pipe;
}					t_cmd;

typedef struct s_flags
{
	int				cmd_flag;
	int				redirection_flag;
	int				pipe_flag;
}					t_flags;

// lexing

int					handle_token_quotes(char *line, int *i);
int					handle_special_chars(char *line, int *i);
int					handle_normal_chars(char *line, int *i);
int					handle_spaces(char *line, int *i);
int					count_tokens(char *line);

char				*trimmer(char *str);
void				expand_token(t_token *current, t_env **env);
void				trim_token(t_token *current);
void				expand_token_list(t_token **token_list, t_env **env);

void				handle_exp_quotes(char *line, char *current_quote,
						int *expand, int *i);
void				append_char(char **res, char *line, int *i);
void				handle_expansion(char **res, char *line, int *i,
						t_env **env);
char				*expander(char *line, t_env **env);

int					is_space(char c);
void				print_strings(char **tokens);

void				print_token_list(t_token **token_list);

void				handle_string_quotes(char *line, char **tokens, int *i,
						int *j);
void				handle_redirection(char *line, char **tokens, int *i,
						int *j);
void				handle_space(char *line, char **tokens, int *i, int *j);
void				handle_general(char *line, char **tokens, int *i, int *j);
char				**line_to_strings(char *line);

void				update_arg_cmd_flags(t_token *new_node, t_flags *flags);
void				update_token_flags(t_token *new_node, t_flags *flags);

void				process_arg_cmd(t_token **current, t_token **new_list,
						t_token **last_new_node, t_flags *flags);
void				copy_non_arg_cmd(t_token **current, t_token **new_list,
						t_token **last_new_node, t_flags *flags);
void				process_current_token(t_token **current, t_token **new_list,
						t_token **last_new_node, t_flags *flags);
t_token				**merge_tokens(t_token **token_list);

void				free_new_list(t_token *new_list);
char				*merge_values(char *merged_value, char *next_value);
t_token				**create_merged_list(t_token *new_list);
void				initialize_merge_vars(t_token **current,
						t_token **token_list, t_flags *flags);
void				add_new_node(t_token **new_list, t_token **last_new_node,
						char *value, int type);

int					check_quote_problems(char *line);
int					redirection_flag_updater(char *line, int *i, int len);
int					check_redirection_problems(char *line);
int					check_pipe_problems(char *line);
int					check_problems(char *line, t_env **env);

void				remove_quotes(char *str, int len);
int					find_env_var_length(char *str, int i);
t_env				*find_env_var(t_env *env, char *str, int i, int j);
void				handle_env_var(char *str, int *i, int *len, t_env **env);
void				check_env_var(char *str, t_env **env);
void				handle_dollar_question(char *str, int *i, t_env **env,
						int *len);
void				handle_quotes(char *str, int *len, int *quote_flag);
void				increment_shlvl(t_env *env);

t_token				**initialize_token_list(void);
int					process_token(char **tokens, int *i, t_env **env);
void				update_str_with_quotes(char *str);

t_token				*create_token_node(char *value);
void				add_token_to_list(t_token **token_list, t_token *new_node);
void				update_flags(t_token *new_node, int *cmd_flag,
						int *redirection_flag);
t_token				**strings_to_tokens(char **tokens, t_env **env);

int					check_token_chars(char *token, int len);
int					get_token_type(char *token);

t_env				**store_env(char **envp);
char				*get_env_value(char *key, t_env **env);

// cleaning_utils.c

void				free_char_tab(char **tab);
void				free_env(t_env **env);
void				free_token_list(t_token **token_list);
void				free_everything(t_env **env, t_token **token, int code_exi);
void				close_dup(t_env **env);

// signals.c

void				handle_sigint(int code);
void				signals(int flag);

// here_doc.c

void				initialise_file_n(t_token **tokens);

// builtins

int					ft_pwd(t_env **env);
int					ft_cd(t_token *tokens, t_env **env);
int					ft_export(t_token *tokens, t_env **env);
int					parsing_export(char *str);
int					printenv(t_env **env, t_token *lst);
void				ft_exit(t_token **tokens, t_token *lst, t_env **env);
int					ft_echo(t_token *tok, t_env **env);
int					is_flag(char *str);
int					skip_flag(char *str);
void				print_env_in_order(t_env **env);
void				exit_status(int code_exit, t_env *env);
void				ft_unset(t_token *token, t_env **env);
void				add_new_env_node(char *key, char *value, t_env **env);
t_token				*skip_redirect(t_token *lst, int flag[2]);

// execute.c

int					access_cmd(t_token *lst, t_token **tokens, t_env **env);
int					count_len(t_token **tokens, t_cmd *cmd);
int					check_pipe(t_token **tokens);
int					handle_here_doc(t_token **tokens, t_env **env);
void				parse_exec(t_token **tokens, t_env **env);
int					ft_strcmp(const char *s1, const char *s2);
int					check_builtins(t_token *lst, t_token **tokens, t_env **env);
char				**initialise_cmd_env(t_env **env);
int					do_cmd(t_token **tokens, t_token *lst, t_env **env);
int					last_cmd(t_token **tokens, t_token *lst, t_env **env);
int					heredoc(t_token *lst, t_env **env);
int					init_std(t_env *env);
int					ft_redirect(int type, t_token *lst);
void				close_redirect(t_token **tokens);
t_cmd				*initialise_cmd(t_token **tokens, t_env **env);

#endif
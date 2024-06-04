/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: florian <florian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 05:43:39 by ftilliet          #+#    #+#             */
/*   Updated: 2024/06/04 14:53:30 by florian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# define CMD 0
# define ARG 1
# define PIPE 2
# define OUT 3
# define IN 4
# define APPEND 5
# define HEREDOC 6
# define IS_SPACE 7

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
	struct s_env	*prev;
}					t_env;

typedef struct s_token
{
	char			*value;
	int				type;
	struct s_token	*next;
	struct s_token	*prev;
}					t_token;

typedef struct s_flags
{
	int				cmd_flag;
	int				redirection_flag;
	int				pipe_flag;
}					t_flags;

// builtins

int					ft_pwd(void);
int					printenv(t_env **env);

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
int					check_problems(char *line);

t_token				*create_token_node(char *value);
void				add_token_to_list(t_token **token_list, t_token *new_node);
void				update_flags(t_token *new_node, int *cmd_flag,
						int *redirection_flag);
t_token				**strings_to_tokens(char **tokens);

int					check_token_chars(char *token, int len);
int					get_token_type(char *token);

// cleaning_utils.c

void				free_char_tab(char **tab);
void				free_env(t_env **env);
void				free_token_list(t_token **token_list);

// env.c

t_env				*create_env_node(char *env_str);
void				append_env_node(t_env **env, t_env *new_node);
t_env				**store_env(char **envp);
char				*get_env_value(char *key, t_env **env);

// signals.c

void				handle_sigint(int code);
void				signals(void);

#endif
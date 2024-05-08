/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: florian <florian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 05:43:39 by ftilliet          #+#    #+#             */
/*   Updated: 2024/05/08 12:41:21 by florian          ###   ########.fr       */
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

// env.c

t_env				*create_env_node(char *env_str);
void				append_env_node(t_env **env, t_env *new_node);
t_env				**store_env(char **envp);
int					printenv(t_env **env);
char				*get_env_value(char *key, t_env **env);

// expander.c

char				*expander(char *line, t_env **env);

// lexer.c

int					is_space(char c);
char				**line_to_strings(char *line);
void				print_tokens(char **tokens);
int					check_quote_problems(char *line);
int					count_tokens(char *line);
t_token				**strings_to_tokens(char **tokens);
void				print_token_list(t_token **token_list);
int					get_token_type(char *token);
void				expand_token(t_token *current, t_env **env);
void				trim_token(t_token *current);
void				expand_token_list(t_token **token_list, t_env **env);

// cleaning_utils.c

void				free_char_tab(char **tab);
void				free_env(t_env **env);
void				free_token_list(t_token **token_list);

// signals.c

void				signals(void);
void				sigint_handler(int code);

// builtins

int					ft_pwd(void);

#endif
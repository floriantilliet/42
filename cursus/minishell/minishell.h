/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: florian <florian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 05:43:39 by ftilliet          #+#    #+#             */
/*   Updated: 2024/04/10 13:50:47 by florian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <readline/history.h>
# include <readline/readline.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <signal.h>

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
	struct s_env 	*prev;
}					t_env;

typedef struct s_token
{
	char			*value;
	int				type;
	struct s_token	*next;
	struct s_token	*prev;
}					t_token;

t_env				**store_env(char **envp);
void				printenv(t_env **env);
char				*get_env_value(char *key, t_env **env);
char				*expander(char *line, t_env **env);

int 				is_space(char c);
char				**lexer(char *line);
void				print_tokens(char **tokens);
int					check_quote_problems(char *line);
int					count_tokens(char *line);
t_token				**tokenizer(char **tokens);
void				print_token_list(t_token **token_list);

void				free_char_tab(char **tab);
void				free_env(t_env **env);
void				free_token_list(t_token **token_list);

void		signals();
void 		sigint_handler(int code);

#endif
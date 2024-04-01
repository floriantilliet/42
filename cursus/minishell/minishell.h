/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: florian <florian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 05:43:39 by ftilliet          #+#    #+#             */
/*   Updated: 2024/04/01 16:52:28 by florian          ###   ########.fr       */
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

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}					t_env;

typedef struct s_token
{
	char			*value;
	int 			type;
	struct s_token	*next;
}					t_token;

t_env				**store_env(char **envp);
void				printenv(t_env **env);
void				free_env(t_env **env);
char				*get_env_value(char *key, t_env **env);
char				*expander(char *line, t_env **env);

char				**lexer(char *line);
void				print_tokens(char **tokens);
int					check_quote_problems(char *line);

#endif
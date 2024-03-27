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

t_env				**store_env(char **envp);
void				printenv(t_env **env);
void				free_env(t_env **env);
char				*get_env_value(char *key, t_env **env);
m
char				*expander(char *line, t_env **env);

#endif
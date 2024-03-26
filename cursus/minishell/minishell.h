#ifndef MINISHELL_H
# define MINISHELL_H

#include "libft/libft.h"

#include <stdio.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>

typedef struct s_env
{
    char *key;
    char *value;
    struct s_env *next;
} t_env;

void	ft_envadd_back(t_env **head, t_env *new);
t_env	*ft_envnew(char* content);

#endif
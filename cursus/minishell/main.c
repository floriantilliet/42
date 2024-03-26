#include "minishell.h"

t_env **store_env(char **envp)
{
    t_env **env;
    int i;

    i = 0;
    while(envp[i])
        i++;
    env = malloc(sizeof(t_env *) * (i + 1));
    if (!env)
        return (NULL);
    while(envp[i])
    {
        ft_envadd_back(env, ft_envnew(envp[i]));
        printf("%s\n", env->value);
    }
    return (env);
}

void printenv(t_env **env)
{
    t_env *current;

    current = *env;
    while(current)
    {
        printf("%s\n", current->value);
        current = current->next;
    }
}

int	main(int ac, char **av, char **envp)
{
	char *line;
	size_t len;

	(void)av;
	(void)ac;
    
    while(*envp)
    {
        printf("%s\n", *envp);
        envp++;
    }

    printf("\n\n");
    t_env **env = NULL;
    env = store_env(envp);
    printenv(env);


	while (1)
	{
		len = 0;
		line = NULL;
		line = readline("minishell $> ");
		if (line)
		{
			add_history(line);
			printf("%s\n", line);
		}
		free(line);
	}

	return (0);
}
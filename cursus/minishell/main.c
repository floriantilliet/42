#include "minishell.h"

t_env **store_env(char **envp)
{
    t_env **env;
    t_env *current;
    t_env *new_node;
    int i;

    i = 0;
    env = (t_env **)malloc(sizeof(t_env *));
    *env = NULL;
    while(*envp)
    {
        current = *env;
        new_node = (t_env *)malloc(sizeof(t_env));
        char *equals_sign = strchr(*envp, '=');
        size_t length = equals_sign - *envp;
        new_node->key = malloc(length + 1);
        strncpy(new_node->key, *envp, length);
        new_node->key[length] = '\0';
        new_node->value = ft_strdup(ft_strchr(*envp, '=') + 1);
        new_node->next = NULL;
        
        if (current == NULL)
        {
            *env = new_node;
        }
        else
        {
            while (current->next != NULL)
            {
                current = current->next;
            }
            current->next = new_node;
        }
        
        envp++;
    }
    return (env);
}

void printenv(t_env **env)
{
    t_env *current;

    current = *env;
    while(current)
    {
        printf("%s=%s\n", current->key, current->value);
        current = current->next;
    }
}

int	main(int ac, char **av, char **envp)
{
	char *line;
	size_t len;

	(void)av;
	(void)ac;


    if(!*envp)
    {
        printf("No environment variables found\n");
        return (1);
    }
    
    t_env **env = NULL;
    env = store_env(envp);

	while (1)
	{
		len = 0;
		line = NULL;
		line = readline("minishell $> ");
		if (line)
		{
			add_history(line);
            if (ft_strncmp(line, "exit", 4) == 0)
            {
                free(line);
                break;
            }
            else if (ft_strncmp(line, "env", 3) == 0)
            {
                printenv(env);
            }
            else
			printf("%s\n", line);
		}
		free(line);
	}

	return (0);
}
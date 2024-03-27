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

void free_env(t_env **env)
{
    t_env *current;
    t_env *next;

    current = *env;
    while(current)
    {
        next = current->next;
        free(current->key);
        free(current->value);
        free(current);
        current = next;
    }
    free(env);
}

char *get_env_value(char *key, t_env **env)
{
    t_env *current;

    current = *env;
    if (ft_strlen(key) == 0)
        return ("");
    while(current)
    {
        if (ft_strncmp(current->key, key, ft_strlen(key)) == 0 && current->key[ft_strlen(key)] == '\0')
        {
            return (current->value);
        }
        current = current->next;
    }
    return ("");
}

char* expander(char *line, t_env **env)
{
    char *res;
    int i;
    int j;
    int expand;

    res = ft_strdup("");
    i = 0;
    expand = 1;
    while (line[i])
    {
        if (line[i] == '\'')
        {
            if (expand == 1)
                expand = 0;
            else
                expand = 1;
        }
        if(line[i] == '$' && expand == 1)
        {
            i++;
            j = 0;
            while (line[i+j] != ' ' && line[i+j] != '\0' && line[i+j] != '$' && line[i+j] != '"')
                j++;
            if (j == 0)
                res = ft_strjoin(res, "$");
            else
            {
                res = ft_strjoin(res, get_env_value(ft_substr(line, i, j), env));
                i += j;
            }
        }
        else
        {
            res = ft_strjoin(res, ft_substr(line, i, 1));
            i++;
        }
    }
    return(res);
}

void lexer(char *line, t_env **env)
{
    expander(line, env);
}

int	main(int ac, char **av, char **envp)
{
	char *line;
	size_t len;

	(void)av;
	(void)ac;

    if(!*envp || !envp)
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
			printf("%s\n", expander(line,env));
		}
		free(line);
	}
    free_env(env);
	return (0);
}
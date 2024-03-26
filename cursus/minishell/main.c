#include "minishell.h"

char **store_env(char **envp)
{
    char **env;
    int i;
    int len;

    len = 0;
    while(envp[len])
        len++;
    env = (char **)malloc(sizeof(char *) * (len + 1));
    i = 0;
    while(i < len)
    {
        env[i] = ft_strdup(envp[i]);
        i++;
    }
    env[i] = NULL;
    return (env);
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
#include "minishell.h"

int	main(int ac, char **av)
{
	char *line;
	size_t len;
	(void)av;
	(void)ac;
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
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftilliet <ftilliet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 05:41:13 by ftilliet          #+#    #+#             */
/*   Updated: 2024/03/27 05:43:49 by ftilliet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **envp)
{
	char *line;
	size_t len;

	(void)av;
	(void)ac;

	if (!*envp || !envp)
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
				break ;
			}
			else if (ft_strncmp(line, "env", 3) == 0)
			{
				printenv(env);
			}
			else
				printf("%s\n", expander(line, env));
		}
		free(line);
	}
	free_env(env);
	return (0);
}
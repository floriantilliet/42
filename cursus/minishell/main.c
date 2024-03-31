/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: florian <florian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 05:41:13 by ftilliet          #+#    #+#             */
/*   Updated: 2024/03/31 19:08:17 by florian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **envp)
{
	char	*line;
	t_env	**env;

	(void)av;
	(void)ac;
	if (!*envp || !envp)
	{
		printf("No environment variables found\n");
		return (1);
	}
	env = NULL;
	env = store_env(envp);
	while((line = readline("minishell $> ")) != NULL)
	{
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
				// printf("%s\n", expander(line, env));
			{
				if (!check_quote_problems(line))
					printf("Error: unclosed quote\n");
				else
					print_tokens(lexer(line));
			}
		}
		free(line);
	}
	free_env(env);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: florian <florian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 05:41:13 by ftilliet          #+#    #+#             */
/*   Updated: 2024/06/02 11:58:36 by florian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

int	main(int ac, char **av, char **envp)
{
	char	*line;
	t_env	**env;
	t_token	**tokens;

	(void)av;
	(void)ac;
	if (!*envp || !envp)
	{
		printf("No environment variables found\n");
		return (1);
	}
	env = NULL;
	env = store_env(envp);
	signals();
	line = "\0";
	while (line != NULL)
	{
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
			else if (ft_strncmp(line, "pwd", 3) == 0)
			{
				ft_pwd();
			}
			else
			// printf("%s\n", expander(line, env));
			{
				if (!check_problems(line))
					;
				else
				{
					tokens = (strings_to_tokens(line_to_strings(line)));
					expand_token_list(tokens, env);
					print_token_list(tokens);
					free_token_list(tokens);
				}
			}
		}
		free(line);
	}
	rl_clear_history();
	free_env(env);
	return (0);
}

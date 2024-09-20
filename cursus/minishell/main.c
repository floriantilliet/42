/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftilliet <ftilliet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 15:05:27 by ochetrit          #+#    #+#             */
/*   Updated: 2024/09/11 20:38:54 by ochetrit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

int			g_exit_code = 0;

static int	rl_resync(void)
{
	return (1);
}

t_env	**init_main(char **envp)
{
	t_env	**env;

	if (!*envp || !envp)
	{
		ft_printf("No environment variables found\n", 2);
		exit(1);
	}
	env = NULL;
	env = store_env(envp);
	if (!env)
		exit(1);
	increment_shlvl(*env);
	signals(PROMPT);
	(*env)->fd_in = dup(STDIN_FILENO);
	(*env)->fd_out = dup(STDOUT_FILENO);
	exit_status(0, *env);
	return (env);
}

void	handle_sig_exit_code(t_env **env)
{
	if (g_exit_code == SIGINT)
	{
		exit_status(130, *env);
		g_exit_code = 0;
	}
	if (g_exit_code == SIGQUIT)
	{
		exit_status(131, *env);
		g_exit_code = 0;
	}
}

void	tokens_and_exec(char *line, t_env **env)
{
	t_token	**tokens;

	tokens = (merge_tokens(strings_to_tokens(line_to_strings(line), env)));
	expand_token_list(tokens, env);
	initialise_file_n(tokens);
	if (!tokens || !*tokens)
		exit_status(0, *env);
	else if (!check_pipe(tokens))
		exit_status(2, *env);
	else if (handle_here_doc(tokens, env))
		parse_exec(tokens, env);
	free_token_list(tokens);
	init_std(*env);
}

int	main(int ac, char **av, char **envp)
{
	char	*line;
	t_env	**env;

	(void)av;
	(void)ac;
	env = init_main(envp);
	line = "\0";
	while (line != NULL)
	{
		rl_event_hook = rl_resync;
		handle_sig_exit_code(env);
		line = readline("minishell $> ");
		if (line)
		{
			add_history(line);
			if (!check_problems(line, env))
				;
			else
				tokens_and_exec(line, env);
		}
		free(line);
	}
	rl_clear_history();
	free_env(env);
	return (0);
}

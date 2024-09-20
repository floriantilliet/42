/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochetrit <ochetrit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 13:13:24 by florian           #+#    #+#             */
/*   Updated: 2024/09/11 20:12:35 by ochetrit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

void	handle_sigint(int code)
{
	(void)code;
	(void)g_exit_code;
	g_exit_code = SIGINT;
	rl_done = 1;
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	ctrl_c_here_doc(int code)
{
	(void)code;
	g_exit_code = SIGINT;
	close(STDIN_FILENO);
	rl_done = 1;
}

void	ctrl_c_child(int code)
{
	(void)code;
	g_exit_code = SIGINT;
	ft_printf("\n", STDOUT_FILENO);
	rl_done = 1;
}

void	sigquit_child(int code)
{
	(void)code;
	g_exit_code = SIGQUIT;
	ft_printf("Quit (core dumped)\n", STDOUT_FILENO);
	rl_done = 1;
}

void	signals(int flag)
{
	if (flag == PROMPT)
	{
		signal(SIGINT, &handle_sigint);
		signal(SIGQUIT, SIG_IGN);
	}
	else if (flag == HERE_DOC)
		signal(SIGINT, &ctrl_c_here_doc);
	else if (flag == CHILD)
	{
		signal(SIGINT, &ctrl_c_child);
		signal(SIGQUIT, &sigquit_child);
	}
}

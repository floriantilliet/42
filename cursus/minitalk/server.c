/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftilliet <ftilliet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 17:04:43 by florian           #+#    #+#             */
/*   Updated: 2024/01/29 18:00:17 by ftilliet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"
#include <stdio.h>

void	bin_to_char(int signum, char *c)
{
	if (signum == SIGUSR1)
		*c = (*c << 1) | 1;
	else if (signum == SIGUSR2)
		*c = (*c << 1) | 0;
}

void	sig_handler(int signum, siginfo_t *info, void *context)
{
	static char	c;
	static char	*str;
	static int	i;

	(void)context;
	(void)info;
	bin_to_char(signum, &c);
	if (++i == 8)
	{
		i = 0;
		if (c == '\0')
		{
			ft_putstr_fd(str, 1);
			write(1, "\n", 1);
			// free(str);
			str = NULL;
			kill(info->si_pid, SIGUSR1);
			return ;
		}
		if (!str)
			str = ft_strdup(&c);
		else
			str = ft_strjoin(str, &c);
		c = 0;
	}

	kill(info->si_pid, SIGUSR2);
}

int	main(void)
{
	struct sigaction	sa;

	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART | SA_SIGINFO;
	sa.sa_sigaction = sig_handler;
	write(1, "PID: ", 5);
	ft_putnbr_fd(getpid(), 1);
	write(1, "\n", 1);
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	while (1)
		pause();
	return (0);
}

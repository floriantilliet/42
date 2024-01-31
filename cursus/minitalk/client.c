/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftilliet <ftilliet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 13:21:50 by florian           #+#    #+#             */
/*   Updated: 2024/01/31 10:57:54 by ftilliet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

int		g_bit_received = 0;

void	sig_handler(int signum, siginfo_t *info, void *context)
{
	(void)context;
	(void)info;
	(void)signum;
	if (signum == SIGUSR2)
		g_bit_received = 1;
	else if (signum == SIGUSR1)
	{
		write(1, "Message received\n", 17);
		exit(0);
	}
}

void	send_bit(int pid, char c, int *i)
{
	if ((c >> *i) & 1)
		kill(pid, SIGUSR1);
	else
		kill(pid, SIGUSR2);
	while (g_bit_received == 0)
		usleep(100);
	g_bit_received = 0;
	(*i)--;
}

void	send_null_byte(int pid, int *i)
{
	while (*i)
	{
		kill(pid, SIGUSR2);
		while (g_bit_received == 0)
			usleep(100);
		g_bit_received = 0;
		(*i)--;
	}
}

void	str_to_bin(int pid, char *str)
{
	int		i;
	char	c;

	while (*str)
	{
		i = 7;
		c = *str++;
		while (i >= 0)
			send_bit(pid, c, &i);
	}
	if (*str == '\0')
	{
		i = 8;
		send_null_byte(pid, &i);
	}
}

int	main(int ac, char **av)
{
	struct sigaction	sa;
	int					pid;

	if (ac != 3 || !ft_strlen(av[2]))
		return (1);
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART | SA_SIGINFO;
	sa.sa_sigaction = sig_handler;
	pid = ft_atoi(av[1]);
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	str_to_bin(pid, av[2]);
	str_to_bin(pid, "");
	while (1)
		sleep(1);
	return (0);
}

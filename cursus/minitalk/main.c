/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: florian <florian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 13:21:50 by florian           #+#    #+#             */
/*   Updated: 2024/01/26 18:18:49 by florian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

int pid = 0;

void sig_handler(int signum, siginfo_t* info, void* context)
{
   (void)context;
   (void)info;
   (void)signum;
   exit(0);
}

void  char_to_bin(int pid, char *str)
{
	int		i;
	char	c;

	while (*str)
	{
		i = 7;
		c = *str++;
		while (i>=0)
		{
			if (c >> i & 1)
				kill(pid, SIGUSR1);
			else
				kill(pid, SIGUSR2);
			usleep(100);
         i--;
		}
   }
   if (*str == '\0')
   {
      i = 8;
      while (i--)
      {
         kill(pid, SIGUSR2);
         usleep(100);
      }
   }
}

int main(int ac, char** av)
{
   struct sigaction sa;
   ac++;

   sigemptyset(&sa.sa_mask);
   sa.sa_flags = SA_RESTART | SA_SIGINFO;
   sa.sa_sigaction = sig_handler;
   printf("pid: %d\n", getpid());
   pid = atoi(av[1]);
   sigaction(SIGUSR1, &sa, NULL);
   char_to_bin(pid, av[2]);
   char_to_bin(pid, "\0");
   while (1)
      sleep(1);
   return (0);
}
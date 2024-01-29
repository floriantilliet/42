/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftilliet <ftilliet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 13:21:50 by florian           #+#    #+#             */
/*   Updated: 2024/01/29 15:17:36 by ftilliet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

int bit_received = 1;

void sig_handler(int signum, siginfo_t* info, void* context)
{
   (void)context;
   (void)info;
   (void)signum;
   if (signum == SIGUSR2)
      bit_received = 1;
   if (signum == SIGUSR1)
   {
      write(1, "Message received\n", 17);
      exit(0);
   }
}

void  str_to_bin(int pid, char *str)
{
	int		i;
	char	c;

   if (bit_received)
   {
      bit_received = 0;
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
   // else
   // {
   //    i = 0;
   //    while(i++ < 50)
   //       usleep(100);
   // }
}

int main(int ac, char** av)
{
   struct sigaction sa;
   int pid;
   ac++;

   sigemptyset(&sa.sa_mask);
   sa.sa_flags = SA_RESTART | SA_SIGINFO;
   sa.sa_sigaction = sig_handler;
   pid = atoi(av[1]);
   sigaction(SIGUSR1, &sa, NULL);
   sigaction(SIGUSR2, &sa, NULL);
   str_to_bin(pid, av[2]);
   str_to_bin(pid, "\0");
   while (1)
      sleep(1);
   return (0);
}
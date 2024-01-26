/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: florian <florian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 17:04:43 by florian           #+#    #+#             */
/*   Updated: 2024/01/26 18:19:21 by florian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <signal.h>
#include <stdio.h>

void bin_to_char(int signum, char *c)
{
   if (signum == SIGUSR1)
      *c = (*c << 1) | 1;
   else if (signum == SIGUSR2)
      *c = (*c << 1) | 0;
}

void sig_handler(int signum, siginfo_t* info, void* context)
{
   static char c;
   static int i;
   // static char *str;

   (void)context;
   (void)info;
   bin_to_char(signum, &c);
   if (i == 7)
   {
      i = 0;
      write(1, &c, 1);
      if (c == '\0')
      {
         write(1, "\n", 1);
         // free(str);
         // str = NULL;
         kill(info->si_pid, SIGUSR1);
         return ;
      }
   }
   else
      i++;
   // kill(info->si_pid, SIGUSR1);
}

int main(void)
{
   struct sigaction sa;
  
   sigemptyset(&sa.sa_mask);
   sa.sa_flags = SA_RESTART | SA_SIGINFO;
   sa.sa_sigaction = sig_handler;
   printf("pid: %d\n", getpid());
   sigaction(SIGUSR1, &sa, NULL);
   sigaction(SIGUSR2, &sa, NULL);
   while (1)
     pause();
   return (0);
}

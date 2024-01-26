/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: florian <florian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 17:04:43 by florian           #+#    #+#             */
/*   Updated: 2024/01/23 17:08:30 by florian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <signal.h>
#include <stdio.h>

void sig_handler(int signum, siginfo_t* info, void* context)
{
   (void)context;
   (void)info;
   (void)signum;
   printf("\nwsh\n");
}

int main(void)
{
   struct sigaction sa;
  
   sigemptyset(&sa.sa_mask);
   sa.sa_flags = SA_RESTART | SA_SIGINFO;
   sa.sa_sigaction = sig_handler;
   printf("pid: %d\n", getpid());
   sigaction(SIGUSR1, &sa, NULL);
   while (1)
     sleep(1);
   return (0);
}

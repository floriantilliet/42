/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: florian <florian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 13:21:50 by florian           #+#    #+#             */
/*   Updated: 2024/01/23 17:19:23 by florian          ###   ########.fr       */
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
   printf("\nSignal handler function called %d\n", signum);
   kill(pid, SIGUSR1);
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
   sigaction(SIGINT, &sa, NULL);
   while (1)
     sleep(1);
   return (0);
}
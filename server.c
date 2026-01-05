/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpedraza <mpedraza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/28 16:29:37 by mpedraza          #+#    #+#             */
/*   Updated: 2026/01/05 18:02:48 by mpedraza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	print_welcome(void)
{
	pid_t	pid;

	pid = getpid();
	ft_printf("*******  WELCOME TO MINITALK ******* \n");
	ft_printf("*                                  * \n");
	ft_printf("*	     ._.)/\\(._.            * \n");
	ft_printf("*                                  * \n");
	ft_printf("* ʕっ•ᴥ•ʔっ SERVER PID: [ %d ] * \n", pid);
	ft_printf("************************************ \n");
	ft_printf("To send a message, run:\n", pid);
	ft_printf("./client %d \"your message\"\n", pid);
	ft_printf("************************************ \n");
}

void	set_client_state(t_client *client, pid_t pid, sig_atomic_t bc, char ch)
{
	client->pid = pid;
	client->bit_count = bc;
	client->ch = ch;
}

void	print_msg(int sig, siginfo_t *info, void *ucontext)
{
	static t_client	client;
	unsigned char	c;

	(void)ucontext;
	if (client.pid == 0 || client.pid != info->si_pid)
		set_client_state(&client, info->si_pid, 0, 0);
	if (sig == SIGUSR1)
		client.ch |= (1 << client.bit_count);
	client.bit_count++;
	if (client.bit_count < 8)
		kill(client.pid, SIGUSR1);
	if (client.bit_count == 8)
	{
		c = client.ch;
		write(1, &c, 1);
		if (client.ch == 0)
		{
			write(1, "\n", 1);
			kill(client.pid, SIGUSR2);
		}
		else
			kill(client.pid, SIGUSR1);
		client.bit_count = 0;
		client.ch = 0;
	}
}

int	main(void)
{
	struct sigaction	message;

	message.sa_flags = SA_RESTART | SA_SIGINFO;
	sigemptyset(&message.sa_mask);
	message.sa_sigaction = print_msg;
	sigaction(SIGUSR1, &message, NULL);
	sigaction(SIGUSR2, &message, NULL);
	print_welcome();
	while (1)
		pause();
	return (0);
}

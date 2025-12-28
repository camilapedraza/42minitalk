/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpedraza <mpedraza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/28 16:29:37 by mpedraza          #+#    #+#             */
/*   Updated: 2025/12/28 23:08:49 by mpedraza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// signal, sigemptyset, sigaddset, sigaction, kill, pause, sleep, usleep, getpid
// write, malloc, free, exit

// Server checklist
// Display its PID
// Create an endless loop so that the server can receive signals at any time
// Receive signals
// Decrypt signals
// For each signal received (SIGUSR1 or SIGUSR2) it should take a certain action

#include "minitalk.h"

void	print_msg(int sig)
{
	static int				bit_count = 0; // start at bit index 0 from LSB
	static unsigned char	ch = 0; // initialize to null char

	if (sig == SIGUSR1)
		ch |= (1 << bit_count); // set bit to 1
	bit_count++;
	if (bit_count == 8) // all bits have been set for char
	{
		// add condition here for when ch == 0?
		write(1, &ch, 1); // print character
		bit_count = 0;
		ch = 0;
	}
}
int	main(void)
{
	// get PID so client can use it
	// handle two allowed signals SIGUSR1 and SIGUSR2
	int					pid;
	struct sigaction	action;

	action.sa_handler = print_msg;
	action.sa_flags = SA_RESTART;
	sigemptyset(&action.sa_mask);
	sigaction(SIGUSR1, &action, NULL);
	sigaction(SIGUSR2, &action, NULL);
	pid = getpid();
	ft_printf("### Welcome to Minitalk ###\n");
	ft_printf("Minitalk Server PID:\n%d\n", pid);
	ft_printf("Run ./client %d \"your message\" to send a message\n", pid);
	while (1)
		pause();
	return 0;
}

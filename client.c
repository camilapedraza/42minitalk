/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpedraza <mpedraza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/28 17:17:16 by mpedraza          #+#    #+#             */
/*   Updated: 2025/12/28 23:17:48 by mpedraza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Client Checklist
// main program takes two parameters (PID of server, message)
// it encrypts the message (via bits)?
// sends the message to the server (via bits)?
// create a stop condition so the server knows the message is over (a stop codon?)

#include "minitalk.h"

static int ft_atoi(const char *nptr)
{
	int val;
	int n;

	val = 1;
	n = 0;
	while ((*nptr == ' ') || (*nptr >= 9 && *nptr <= 13))
		nptr++;
	if (*nptr == '-' || *nptr == '+')
	{
		if (*nptr == '-')
			val = val * -1;
		nptr++;
	}
	while (*nptr >= '0' && *nptr <= '9')
	{
		n = n * 10 + (*nptr - '0');
		nptr++;
	}
	return (n * val);
}

static void send_char(pid_t pid, char ch)
{
	int i;
	
	i = 0;
	while (i < 8)
	{
		if (ch & (1 << i)) 
			kill(pid, SIGUSR1); // send 1
		else
			kill(pid, SIGUSR2); // send 0
		usleep(500);
		i++;
	}
}

static void send_msg(pid_t pid, char *str)
{
	int i = 0;
	while (str[i])
	{
		send_char(pid, str[i]);
		i++;
	}
	send_char(pid, '\0');
}

int	main(int ac, char **av)
{
	int	pid;
	if (ac != 3)
		exit(EXIT_SUCCESS);
	pid = ft_atoi(av[1]);
	send_msg(pid, av[2]);
	return (0);
}
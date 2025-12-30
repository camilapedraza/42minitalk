/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpedraza <mpedraza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/28 17:17:16 by mpedraza          #+#    #+#             */
/*   Updated: 2025/12/30 17:47:20 by mpedraza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

volatile sig_atomic_t	g_acknowledged = 0;

void	ack_handler(int sig)
{
	(void)sig;
	g_acknowledged = 1;
}

static int	ft_atoi(const char *nptr)
{
	int	val;
	int	n;

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

static void	send_char(pid_t pid, char ch)
{
	int	i;
	int	elapsed;

	i = 0;
	while (i < 8)
	{
		elapsed = 0;
		if (ch & (1 << i))
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		while (!g_acknowledged && elapsed < ACK_TIMEOUT)
		{
			usleep(ACK_INTERVAL);
			elapsed += ACK_INTERVAL;
		}
		if (!g_acknowledged)
		{
			write(2, "Server Error ʕノ•ᴥ•ʔノ ︵ ┻━┻ \n", 48);
			exit(EXIT_FAILURE);
		}
		g_acknowledged = 0;
		i++;
	}
	g_acknowledged = 0;
}

static void	send_msg(pid_t pid, char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		send_char(pid, str[i]);
		i++;
	}
	send_char(pid, '\0');
	write(1, "ʕっ•ᴥ•ʔっ Message Delivered\n", 38);
}

int	main(int ac, char **av)
{
	pid_t				pid;
	struct sigaction	handshake;

	handshake.sa_flags = SA_RESTART | SA_SIGINFO;
	sigemptyset(&handshake.sa_mask);
	handshake.sa_handler = ack_handler;
	sigaction(SIGUSR1, &handshake, NULL);
	if (ac != 3)
		exit(EXIT_SUCCESS);
	pid = ft_atoi(av[1]);
	send_msg(pid, av[2]);
	return (0);
}

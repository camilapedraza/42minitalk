/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpedraza <mpedraza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/28 17:28:16 by mpedraza          #+#    #+#             */
/*   Updated: 2026/01/05 19:04:55 by mpedraza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

# ifndef _XOPEN_SOURCE
#  define _XOPEN_SOURCE 600
# endif

# ifndef _POSIX_C_SOURCE
#  define _POSIX_C_SOURCE 200809L
# endif

# ifndef ACK_TIMEOUT
#  define ACK_TIMEOUT 1000000
# endif

# ifndef ACK_INTERVAL
#  define ACK_INTERVAL 1000
# endif

# include <signal.h>
# include <unistd.h>
# include <stdlib.h>
# include "ftprintf/ft_printf.h"

typedef struct s_client
{
	pid_t					pid;
	volatile sig_atomic_t	bit_count;
	volatile unsigned char	ch;
}	t_client;

#endif
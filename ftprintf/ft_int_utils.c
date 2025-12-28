/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_int_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpedraza <mpedraza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 14:47:00 by mpedraza          #+#    #+#             */
/*   Updated: 2025/12/28 21:45:25 by mpedraza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	print_nbr(int n, int count)
{
	long	nb;

	nb = (long)n;
	if (nb < 0)
	{
		count = print_chr('-', count);
		nb = -nb;
	}
	if (nb > 9)
	{
		count = print_nbr((nb / 10), count);
		count = print_chr((nb % 10 + 48), count);
	}
	if (nb < 10)
		count = print_chr((nb + 48), count);
	return (count);
}

int	print_uns(unsigned int n, int count)
{
	if (n > 9)
		count = print_uns((n / 10), count);
	count = print_chr((n % 10 + 48), count);
	return (count);
}

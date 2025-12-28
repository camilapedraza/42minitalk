/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hex_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpedraza <mpedraza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 14:47:00 by mpedraza          #+#    #+#             */
/*   Updated: 2025/11/26 17:34:48 by mpedraza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	print_hex(int n, char f, int count)
{
	unsigned int	nb;
	char			base;

	base = 'a';
	if (f == 'X')
		base = 'A';
	nb = (unsigned int)n;
	if (nb > 15)
	{
		count = print_hex((nb / 16), f, count);
		count = print_hex((nb % 16), f, count);
	}
	else
	{
		if (nb < 10)
			count = print_chr((nb + '0'), count);
		else
			count = print_chr((nb - 10 + base), count);
	}
	return (count);
}

int	print_ptr(uintptr_t nb, int count)
{
	if (nb > 15)
	{
		count = print_ptr((nb / 16), count);
		count = print_ptr((nb % 16), count);
	}
	else
	{
		if (nb < 10)
			count = print_chr((nb + '0'), count);
		else
			count = print_chr((nb - 10 + 'a'), count);
	}
	return (count);
}

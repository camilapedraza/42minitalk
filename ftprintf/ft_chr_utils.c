/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_chr_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpedraza <mpedraza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 14:47:00 by mpedraza          #+#    #+#             */
/*   Updated: 2025/11/26 19:59:15 by mpedraza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	print_chr(char chr, int count)
{
	write(1, &chr, 1);
		count++;
	return (count);
}

int	print_str(char *str, int count)
{
	if (!str)
		str = "(null)";
	while (*str)
		count = print_chr(*(str++), count);
	return (count);
}

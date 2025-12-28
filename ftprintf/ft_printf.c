/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpedraza <mpedraza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 14:47:00 by mpedraza          #+#    #+#             */
/*   Updated: 2025/12/28 22:07:39 by mpedraza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	parse_ptr(uintptr_t n, int count)
{
	if (!n)
		count = print_str("(nil)", count);
	else
	{
		count = print_str("0x", count);
		count = print_ptr(n, count);
	}
	return (count);
}

static int	parse_spec(char spec, int count, va_list args)
{
	if (spec == '%')
		count = print_chr('%', count);
	else if (spec == 'c')
		count = print_chr(va_arg(args, int), count);
	else if (spec == 's')
		count = print_str(va_arg(args, char *), count);
	else if (spec == 'd' || spec == 'i')
		count = print_nbr(va_arg(args, int), count);
	else if (spec == 'u')
		count = print_uns((unsigned int)va_arg(args, int), count);
	else if (spec == 'x' || spec == 'X')
		count = print_hex(va_arg(args, int), spec, count);
	else if (spec == 'p')
		count = parse_ptr((uintptr_t)va_arg(args, void *), count);
	else
	{
		count = print_chr('%', count);
		count = print_chr(spec, count);
	}
	return (count);
}

static int	parse_str(va_list args, char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] != '%')
			count = print_chr(str[i], count);
		else
		{
			if (!str[i + 1])
				count = print_chr('%', count);
			else
				count = parse_spec(str[++i], count, args);
		}
		i++;
	}
	return (count);
}

int	ft_printf(const char *f, ...)
{
	int		count;
	char	*str;
	va_list	args;

	count = 0;
	if (!f || !*f)
		return (-1);
	str = (char *)f;
	if (!str)
		return (0);
	va_start(args, f);
	count = parse_str(args, str);
	va_end(args);
	return (count);
}

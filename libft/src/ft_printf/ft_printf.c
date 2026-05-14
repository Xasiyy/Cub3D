/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abollia <abollia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 12:04:03 by abollia           #+#    #+#             */
/*   Updated: 2025/04/14 15:49:21 by abollia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_format(const char c, va_list args)
{
	int	printlen;

	printlen = 0;
	if (c == 'c')
		printlen += ft_printchar(va_arg(args, int));
	else if (c == 's')
		printlen += ft_printstr(va_arg(args, char *));
	else if (c == 'p')
		printlen += ft_printptr(va_arg(args, void *));
	else if (c == 'd' || c == 'i')
		printlen += ft_printnbr(va_arg(args, int));
	else if (c == 'u')
		printlen += ft_printnbru(va_arg(args, unsigned int));
	else if (c == 'x' || c == 'X')
		printlen += ft_printhex(va_arg(args, unsigned int), c);
	else if (c == '%')
		printlen += ft_printchar('%');
	else
	{
		printlen += ft_printchar('%');
		printlen += ft_printchar(c);
	}
	return (printlen);
}

int	ft_printf(const char *str, ...)
{
	size_t			i;
	unsigned int	printlen;
	va_list			args;

	i = 0;
	printlen = 0;
	if (!str)
		return (-1);
	va_start(args, str);
	while (str[i])
	{
		if (str[i] == '%')
		{
			if (str[i + 1] == '\0')
				return (-1);
			printlen += ft_format(str[i + 1], args);
			i++;
		}
		else
			printlen += ft_printchar(str[i]);
		i++;
	}
	va_end(args);
	return (printlen);
}

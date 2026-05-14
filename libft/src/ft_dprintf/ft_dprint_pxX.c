/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dprint_pxX.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abollia <abollia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 11:09:57 by abollia           #+#    #+#             */
/*   Updated: 2025/04/14 15:49:05 by abollia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_dprinthex(int fd, unsigned long long n, const char format)
{
	int		len;
	char	*base;

	len = 0;
	if (format == 'x')
		base = "0123456789abcdef";
	else if (format == 'X')
		base = "0123456789ABCDEF";
	if (n >= 16)
	{
		len += ft_dprinthex(fd, n / 16, format);
		len += ft_dprinthex(fd, n % 16, format);
	}
	else
		len += ft_dprintchar(fd, base[n]);
	return (len);
}

int	ft_dprintptr(int fd, void *p)
{
	int	len;

	len = 0;
	if (!p)
		return (ft_dprintstr(fd, "(nil)"));
	len += ft_dprintstr(fd, "0x");
	len += ft_dprinthex(fd, (unsigned long long)p, 'x');
	return (len);
}

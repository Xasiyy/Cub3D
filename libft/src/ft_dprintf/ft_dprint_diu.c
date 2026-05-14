/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dprint_diu.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abollia <abollia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 11:06:32 by abollia           #+#    #+#             */
/*   Updated: 2025/04/14 15:49:03 by abollia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_dprintnbr(int fd, int n)
{
	long	nb;
	int		len;

	nb = n;
	len = 0;
	if (nb < 0)
	{
		len += ft_dprintchar(fd, '-');
		nb *= -1;
	}
	if (nb > 9)
		len += ft_dprintnbr(fd, (nb / 10));
	len += ft_dprintchar(fd, (nb % 10 + '0'));
	return (len);
}

int	ft_dprintnbru(int fd, unsigned int n)
{
	unsigned long	nb;
	int				len;

	nb = n;
	len = 0;
	if (nb > 9)
		len += ft_dprintnbru(fd, (nb / 10));
	len += ft_dprintchar(fd, (nb % 10 + '0'));
	return (len);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abollia <abollia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 16:00:02 by abollia           #+#    #+#             */
/*   Updated: 2025/04/14 15:52:32 by abollia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_cntnbr(long n)
{
	size_t	len;

	len = 1;
	if (n < 0)
	{
		n = -n;
		len++;
	}
	if (n > 9)
	{
		while (n >= 10)
		{
			n /= 10;
			len++;
		}
	}
	return (len);
}

static char	*ft_taballoc(size_t len)
{
	char	*tab;

	tab = (char *)malloc(sizeof(char) * (len + 1));
	if (!tab)
		return (NULL);
	return (tab);
}

char	*ft_itoa(int n)
{
	size_t	len;
	size_t	i;
	long	nb;
	char	*res;

	nb = n;
	len = ft_cntnbr(nb);
	res = ft_taballoc(len);
	if (!res)
		return (NULL);
	res[len] = '\0';
	if (nb == 0)
		res[0] = '0';
	if (nb < 0)
		nb = -nb;
	i = len - 1;
	while (nb)
	{
		res[i] = (nb % 10) + '0';
		nb /= 10;
		i--;
	}
	if (n < 0)
		res[0] = '-';
	return (res);
}

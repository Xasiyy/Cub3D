/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dprint_cs%.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abollia <abollia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 09:32:55 by abollia           #+#    #+#             */
/*   Updated: 2025/04/14 15:49:00 by abollia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_dprintchar(int fd, int c)
{
	ft_putchar_fd((char)c, fd);
	return (1);
}

int	ft_dprintstr(int fd, const char *str)
{
	size_t	i;

	if (!str)
		str = "(null)";
	i = 0;
	while (str[i])
		i += ft_dprintchar(fd, str[i]);
	return (i);
}

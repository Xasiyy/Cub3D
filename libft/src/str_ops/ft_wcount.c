/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wcount.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abollia <abollia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 13:20:16 by abollia           #+#    #+#             */
/*   Updated: 2025/04/17 13:24:56 by abollia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_wcount(const char *str, int sep)
{
	int		trigger;
	size_t	count;

	trigger = 0;
	count = 0;
	while (*str)
	{
		if (*str != sep && trigger == 0)
		{
			trigger = 1;
			count++;
		}
		else if (*str == sep)
			trigger = 0;
		str++;
	}
	return (count);
}

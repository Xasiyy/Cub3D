/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isonlyspace.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abollia <abollia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/31 12:22:18 by abollia           #+#    #+#             */
/*   Updated: 2025/08/31 12:37:31 by abollia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isonlyspace(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isspace((int)str[i]))
			return (0);
		i++;
	}
	return (1);
}

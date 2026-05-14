/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_secufree.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abollia <abollia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 12:48:04 by abollia           #+#    #+#             */
/*   Updated: 2025/05/08 14:51:48 by abollia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_secufree(void **memspace)
{
	if (memspace && *memspace)
	{
		free(*memspace);
		*memspace = NULL;
	}
}

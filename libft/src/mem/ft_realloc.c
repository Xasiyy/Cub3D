/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abollia <abollia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 14:34:38 by abollia           #+#    #+#             */
/*   Updated: 2025/04/15 15:13:50 by abollia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_realloc(void *ptr, size_t newsize)
{
	void	*new_ptr;

	if (!newsize)
		return (free(ptr), NULL);
	new_ptr = malloc(newsize);
	if (!new_ptr)
		return (NULL);
	if (!ptr)
		return (new_ptr);
	else
	{
		ft_memcpy(new_ptr, ptr, newsize);
		free(ptr);
		return (new_ptr);
	}
}

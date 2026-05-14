/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc_old.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abollia <abollia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 09:36:43 by abollia           #+#    #+#             */
/*   Updated: 2025/04/14 15:50:44 by abollia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_realloc(void *ptr, size_t cursize, size_t newsize)
{
	size_t	sizetocpy;
	void	*newptr;

	if (!newsize)
		return (free(ptr), NULL);
	if (!ptr)
		return ((void *)malloc(newsize));
	if (newsize <= cursize)
		sizetocpy = newsize;
	else
		sizetocpy = cursize;
	newptr = (void *)malloc(newsize);
	if (!newptr)
		return (NULL);
	ft_memcpy(newptr, ptr, sizetocpy);
	free(ptr);
	return (newptr);
}

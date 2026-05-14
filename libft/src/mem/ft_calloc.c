/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abollia <abollia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 12:01:52 by abollia           #+#    #+#             */
/*   Updated: 2025/04/14 15:50:17 by abollia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*blok;
	size_t	totsize;

	totsize = nmemb * size;
	if (nmemb != 0 && totsize / nmemb != size)
		return (NULL);
	blok = (void *)malloc (totsize);
	if (blok == NULL)
		return (NULL);
	ft_bzero(blok, nmemb * size);
	return (blok);
}

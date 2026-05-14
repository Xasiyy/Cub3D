/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_secumalloc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abollia <abollia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 13:15:05 by abollia           #+#    #+#             */
/*   Updated: 2025/04/15 15:13:44 by abollia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_secumalloc(size_t size)
{
	void	*memspace;

	memspace = malloc(size);
	if (!memspace)
	{
		perror("Error - Malloc failed to allocate memory space");
		exit(EXIT_FAILURE);
	}
	return (memspace);
}

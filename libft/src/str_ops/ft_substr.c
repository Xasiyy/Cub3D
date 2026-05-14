/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abollia <abollia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 13:46:39 by abollia           #+#    #+#             */
/*   Updated: 2025/04/14 15:52:21 by abollia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(const char *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	lens;
	char	*zub;

	if (!s)
		return (NULL);
	lens = ft_strlen(s);
	if (start >= lens)
		return (ft_calloc(1, sizeof(char)));
	if (len > lens - start)
		len = lens - start;
	zub = ft_calloc(len + 1, sizeof(char));
	if (!zub)
		return (NULL);
	i = 0;
	while (i < len && s[start + i])
	{
		zub[i] = s[start + i];
		i++;
	}
	zub[i] = '\0';
	return (zub);
}

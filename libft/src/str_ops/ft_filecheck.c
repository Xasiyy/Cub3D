/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_filecheck.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abollia <abollia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 13:53:37 by abollia           #+#    #+#             */
/*   Updated: 2025/10/29 17:43:29 by abollia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_filecheck(char *file, char *ext)
{
	size_t	len;
	size_t	len_ext;

	len = ft_strlen(file);
	len_ext = ft_strlen(ext);
	if (ft_strncmp(&file[len - len_ext], ext, len_ext) || len <= len_ext)
		return (1);
	return (0);
}

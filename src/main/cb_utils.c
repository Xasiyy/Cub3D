/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cb_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asdiallo <asiya040906@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 17:33:13 by abollia           #+#    #+#             */
/*   Updated: 2025/12/11 12:06:51 by asdiallo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	cb_errorhub(char *message, int code, t_data *d)
{
	ft_dprintf(2, "Error\n%s\n", message);
	if (code)
		cb_exithub(1, d);
}

void	cb_exithub(int code, t_data *d)
{
	if (d)
		gc_free_all(d);
	if (code)
		exit(EXIT_FAILURE);
	exit(EXIT_SUCCESS);
}

void	*cb_secumalloc(size_t size, t_data *d)
{
	void	*memspace;

	memspace = malloc(size);
	if (!memspace)
		cb_errorhub(ERR_MALLOC, 1, d);
	return (memspace);
}

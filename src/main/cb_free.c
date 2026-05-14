/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cb_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asdiallo <asiya040906@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 13:40:13 by abollia           #+#    #+#             */
/*   Updated: 2025/12/11 12:07:11 by asdiallo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	cb_free_cub(t_cub *cub)
{
	if (!cub)
		return ;
	if (cub)
	{
		ft_secufree((void **)&cub->n_tex);
		ft_secufree((void **)&cub->s_tex);
		ft_secufree((void **)&cub->w_tex);
		ft_secufree((void **)&cub->e_tex);
		ft_ffa(&cub->m_pat);
		ft_secufree((void **)&cub);
	}
}

static void	cb_free_file(t_file *f)
{
	if (f)
	{
		if (f->fd != -1)
			close(f->fd);
	}
}

void	cb_free(t_data *d)
{
	cb_free_file(d->file);
	cb_free_cub(d->cub);
	gc_free_all(d);
	ft_secufree((void **)&d);
}

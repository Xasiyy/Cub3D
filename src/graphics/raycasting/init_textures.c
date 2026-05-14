/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asdiallo <asiya040906@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 11:29:20 by asdiallo          #+#    #+#             */
/*   Updated: 2025/12/03 10:13:58 by asdiallo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	load_texture(t_data *d, t_img *tex, char *path)
{
	int	w;
	int	h;

	tex->ptr = mlx_xpm_file_to_image(d->mlx, path, &w, &h);
	if (!tex->ptr)
		cb_errorhub("Texture load failed", 1, d);
	tex->addr = mlx_get_data_addr(tex->ptr, &tex->bpp,
			&tex->line_len, &tex->endian);
	tex->width = w;
	tex->height = h;
}

void	load_all_textures(t_data *d)
{
	load_texture(d, &d->tex[0], d->cub->n_tex);
	load_texture(d, &d->tex[1], d->cub->s_tex);
	load_texture(d, &d->tex[2], d->cub->w_tex);
	load_texture(d, &d->tex[3], d->cub->e_tex);
}

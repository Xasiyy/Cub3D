/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asdiallo <asiya040906@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 12:52:48 by asdiallo          #+#    #+#             */
/*   Updated: 2025/12/09 18:09:41 by asdiallo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	render_frame(t_data *d)
{
	compute_rays(d);
	update(d);
	render_3d_view(d);
	draw_minimap(d);
	mlx_put_image_to_window(d->mlx, d->win, d->img.ptr, 0, 0);
	return (0);
}

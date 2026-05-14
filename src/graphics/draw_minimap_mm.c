/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_minimap_mm.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asdiallo <asiya040906@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/01 14:28:27 by xasiy             #+#    #+#             */
/*   Updated: 2025/12/11 12:04:39 by asdiallo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	draw_tile_mm(t_img *img, t_point pos, int size, unsigned int color)
{
	int	dy;
	int	dx;

	dy = 0;
	while (dy < size)
	{
		dx = 0;
		while (dx < size)
		{
			my_pixel_put(img, pos.x + dx, pos.y + dy, color);
			dx++;
		}
		dy++;
	}
}

// size minimap top left
void	mm_setup(t_data *d, int *ox, int *oy, int *t)
{
	int	max_w;
	int	max_h;
	int	tw;
	int	th;
	int	tt;

	max_w = d->win_w * 0.25;
	max_h = d->win_h * 0.25;
	if (max_w < 80)
		max_w = 80;
	if (max_h < 80)
		max_h = 80;
	tw = max_w / d->cub->m_width;
	th = max_h / d->cub->m_height;
	tt = tw;
	if (th < tt)
		tt = th;
	if (tt < 4)
		tt = 4;
	if (tt > 24)
		tt = 24;
	*t = tt;
	*ox = 12;
	*oy = 12;
}

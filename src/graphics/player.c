/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asdiallo <asiya040906@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 23:06:42 by asdiallo          #+#    #+#             */
/*   Updated: 2025/11/11 23:50:11 by asdiallo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	draw_cone_scanline(t_data *d, t_cone *c, int cx, int cy)
{
	int	half;
	int	off;

	half = (int)((c->base * c->t) / c->len);
	off = -half;
	while (off <= half)
	{
		my_pixel_put(&d->img,
			cx + (int)(c->perp_x * off),
			cy + (int)(c->perp_y * off),
			c->color);
		off++;
	}
}

void	draw_player_cone(t_data *d, int px, int py)
{
	t_cone	c;
	int		cx;
	int		cy;

	c.dir = d->player.dir;
	c.perp_x = sin(c.dir);
	c.perp_y = cos(c.dir);
	c.len = 10.0;
	c.base = 5.0;
	c.t = 1.0;
	c.color = 0x00E6E6E6;
	while (c.t <= c.len)
	{
		cx = px + (int)(cos(c.dir) * c.t);
		cy = py - (int)(sin(c.dir) * c.t);
		draw_cone_scanline(d, &c, cx, cy);
		c.t += 1.0;
	}
}

void	draw_player(t_data *d, int ox, int oy, int tile)
{
	int	px;
	int	py;
	int	r;
	int	dx;
	int	dy;

	px = ox + (int)(d->player.x * tile);
	py = oy + (int)(d->player.y * tile);
	r = 3;
	dy = -r;
	while (dy <= r)
	{
		dx = -r;
		while (dx <= r)
		{
			if (dx * dx + dy * dy <= r * r)
				my_pixel_put(&d->img, px + dx, py + dy, 0x00469BBD);
			dx++;
		}
		dy++;
	}
	draw_player_cone(d, px, py);
}

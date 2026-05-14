/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_view.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abollia <abollia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 23:56:30 by xasiy             #+#    #+#             */
/*   Updated: 2025/12/17 10:43:25 by abollia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	draw_ceiling(t_data *d, t_column *c)
{
	int	y;

	y = 0;
	while (y < c->wall_top)
	{
		my_pixel_put(&d->img, c->x, y, d->cub->c_int_col);
		y++;
	}
	if (c->wall_height <= 0)
	{
		while (y < d->win_h)
		{
			my_pixel_put(&d->img, c->x, y, d->cub->c_int_col);
			y++;
		}
		return (-1);
	}
	return (y);
}

int	draw_wall_stripe(t_data *d, t_column *c, int tex_x, int y_start)
{
	double			step;
	double			tex_pos;
	int				y;
	int				tex_y;
	unsigned int	color;

	step = (double)c->tex->height / (double)c->wall_height;
	tex_pos = (c->wall_top - (d->win_h * 0.5)
			+ (c->wall_height * 0.5)) * step;
	y = y_start;
	while (y <= c->wall_bottom)
	{
		tex_y = (int)tex_pos;
		if (tex_y < 0)
			tex_y = 0;
		if (tex_y >= c->tex->height)
			tex_y = c->tex->height -1 ;
		color = *(unsigned int *)(c->tex->addr
				+ tex_y * c->tex->line_len
				+ tex_x * (c->tex->bpp / 8));
		my_pixel_put(&d->img, c->x, y, color);
		tex_pos += step;
		y++;
	}
	return (y);
}

void	draw_wall_column(t_data *d, t_column *c)
{
	int				y;
	int				tex_x;

	y = draw_ceiling(d, c);
	if (y < 0)
		return ;
	tex_x = (int)(c->wall_pos * (double)c->tex->width);
	if (tex_x < 0)
		tex_x = 0;
	if (tex_x >= c->tex->width)
		tex_x = c->tex->width - 1;
	if (c->flip_tex)
		tex_x = c->tex->width - 1 - tex_x;
	y = draw_wall_stripe(d, c, tex_x, y);
	while (y < d->win_h)
	{
		my_pixel_put(&d->img, c->x, y, d->cub->f_int_col);
		y++;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendu_3D.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asdiallo <asiya040906@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 10:36:19 by asdiallo          #+#    #+#             */
/*   Updated: 2025/12/08 23:48:21 by asdiallo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

double	get_ray_angle(t_data *d, int col)
{
	double	angle_start;
	double	angle_step;
	double	angle;

	if (d->num_rays < 2)
		return (d->player.dir);
	angle_start = d->player.dir + (FOV / 2.0);
	angle_step = -FOV / (double)(d->num_rays - 1);
	angle = angle_start + angle_step * (double)col;
	angle = normalize_angle(angle);
	return (angle);
}

void	select_column_tex(t_data *d, t_column *col, double ray_angle, int side)
{
	double	dir_x;
	double	dir_y;

	dir_x = cos(ray_angle);
	dir_y = -sin(ray_angle);
	if (side == 0)
	{
		if (dir_x > 0.0)
			col->tex = &d->tex[3];
		else
			col->tex = &d->tex[2];
	}
	else
	{
		if (dir_y > 0.0)
			col->tex = &d->tex[1];
		else
			col->tex = &d->tex[0];
	}
	col->flip_tex = 0;
	if (col->tex == &d->tex[2] || col->tex == &d->tex[1])
		col->flip_tex = 1;
}

void	fill_column_geom(t_data *d, t_column *col)
{
	double	proj_plane;
	int		wall_top;
	int		wall_bottom;

	proj_plane = (d->win_w / 2.0) / tan(FOV / 2.0);
	col->wall_height = (int)(proj_plane / col->corrected);
	wall_top = (d->win_h / 2) - (col->wall_height / 2);
	wall_bottom = (d->win_h / 2) + (col->wall_height / 2);
	if (wall_top < 0)
		wall_top = 0;
	if (wall_bottom >= d->win_h)
		wall_bottom = d->win_h - 1;
	col->wall_top = wall_top;
	col->wall_bottom = wall_bottom;
}

void	render_one_column(t_data *d, int x)
{
	t_hit		hit;
	t_column	col;
	double		ray_angle;
	double		corrected;

	ray_angle = get_ray_angle(d, x);
	hit = cast_one_ray(d, ray_angle);
	if (!hit.hit)
		return ;
	corrected = apply_fisheye(hit.dist, ray_angle, d->player.dir);
	if (corrected < 0.0001)
		corrected = 0.0001;
	col.x = x;
	col.corrected = corrected;
	col.wall_pos = hit.wall;
	col.flip_tex = 0;
	fill_column_geom(d, &col);
	select_column_tex(d, &col, ray_angle, hit.side);
	draw_wall_column(d, &col);
}

void	render_3d_view(t_data *d)
{
	int			x;

	x = 0;
	while (x < d->num_rays)
	{
		render_one_column(d, x);
		x++;
	}
}

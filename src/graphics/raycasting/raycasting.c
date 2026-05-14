/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abollia <abollia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/22 10:04:02 by asdiallo          #+#    #+#             */
/*   Updated: 2025/12/19 14:07:50 by abollia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	init_rays(t_data *d)
{
	d->num_rays = d->win_w;
	d->rays = gc_malloc(d, sizeof(t_ray) * d->num_rays);
	if (!d->rays)
		cb_errorhub(ERR_MALLOC, 1, d);
}

double	normalize_angle(double a)
{
	while (a < 0.0)
		a += 2.0 * MY_PI;
	while (a >= 2.0 * MY_PI)
		a -= 2.0 * MY_PI;
	return (a);
}

void	compute_rays(t_data *d)
{
	double	fov;
	double	first_angle;
	double	step;
	int		x;

	fov = FOV;
	step = fov / (double)d->num_rays;
	first_angle = d->player.dir - (fov / 2.0);
	x = 0;
	while (x < d->num_rays)
	{
		d->rays[x].angle = normalize_angle(first_angle + (double)x * step);
		x++;
	}
}

t_hit	cast_one_ray(t_data *d, double angle)
{
	t_hit	vh;
	t_hit	hh;
	t_hit	res;

	vh = cast_vertical(d, angle);
	hh = cast_horizontal(d, angle);
	res = hh;
	if (vh.hit == 0 && hh.hit == 1)
		res = hh;
	else if (hh.hit == 0 && vh.hit == 1)
		res = vh;
	else if (vh.hit == 1 && hh.hit == 1 && vh.dist < hh.dist)
		res = vh;
	return (res);
}

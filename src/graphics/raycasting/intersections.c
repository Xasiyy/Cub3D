/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asdiallo <asiya040906@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 16:23:10 by asdiallo          #+#    #+#             */
/*   Updated: 2025/12/03 10:18:14 by asdiallo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	init_cast_vertical(t_data *d, double angle, t_cast *cast)
{
	cast->px = d->player.x;
	cast->py = d->player.y;
	cast->dir_x = cos(angle);
	cast->dir_y = -sin(angle);
	cast->depth = 0;
	cast->max_depth = d->cub->m_width + d->cub->m_height;
	if (cast->dir_x > -0.000001 && cast->dir_x < 0.000001)
		return ;
	if (cast->dir_x > 0.0)
	{
		cast->x = floor(cast->px) + 1.0;
		cast->y = cast->py + (cast->x - cast->px) * (cast->dir_y / cast->dir_x);
		cast->step_x = 1.0;
		cast->step_y = cast->step_x * (cast->dir_y / cast->dir_x);
	}
	else
	{
		cast->x = floor(cast->px) - 0.000001;
		cast->y = cast->py + (cast->x - cast->px) * (cast->dir_y / cast->dir_x);
		cast->step_x = -1.0;
		cast->step_y = cast->step_x * (cast->dir_y / cast->dir_x);
	}
}

void	init_cast_horizontal(t_data *d, double angle, t_cast *cast)
{
	cast->px = d->player.x;
	cast->py = d->player.y;
	cast->dir_x = cos(angle);
	cast->dir_y = -sin(angle);
	cast->depth = 0;
	cast->max_depth = d->cub->m_width + d->cub->m_height;
	if (cast->dir_y > -0.000001 && cast->dir_y < 0.000001)
		return ;
	if (cast->dir_y > 0.0)
	{
		cast->y = floor(cast->py) + 1.0;
		cast->x = cast->px + (cast->y - cast->py) * (cast->dir_x / cast->dir_y);
		cast->step_y = 1.0;
		cast->step_x = cast->step_y * (cast->dir_x / cast->dir_y);
	}
	else
	{
		cast->y = floor(cast->py) - 0.000001;
		cast->x = cast->px + (cast->y - cast->py) * (cast->dir_x / cast->dir_y);
		cast->step_y = -1.0;
		cast->step_x = cast->step_y * (cast->dir_x / cast->dir_y);
	}
}

static void	fill_hit_from_cast(t_hit *hit, t_cast *cast, int side)
{
	double	dx;
	double	dy;

	dy = cast->y - cast->py;
	dx = cast->x - cast->px;
	hit->hit = 1;
	hit->x = cast->x;
	hit->y = cast->y;
	dx = cast->x - cast->px;
	dy = cast->y - cast->py;
	hit->dist = sqrt(dx * dx + dy * dy);
	hit->side = side;
	if (side == 0)
		hit->wall = cast->y - floor(cast->y);
	else
		hit->wall = cast->x - floor(cast->x);
}

t_hit	cast_vertical(t_data *d, double angle)
{
	t_cast	cast;
	t_hit	hit;

	hit.hit = 0;
	hit.dist = 0;
	hit.x = 0.0;
	hit.y = 0.0;
	hit.side = 0;
	hit.wall = 0.0;
	init_cast_vertical(d, angle, &cast);
	if (cast.dir_x > -0.000001 && cast.dir_x < 0.000001)
		return (hit);
	while (cast.depth < cast.max_depth && hit.hit == 0)
	{
		if (is_wall_at(d, cast.x, cast.y))
			fill_hit_from_cast(&hit, &cast, 0);
		else
			step_cast(&cast);
	}
	return (hit);
}

t_hit	cast_horizontal(t_data *d, double angle)
{
	t_cast	cast;
	t_hit	hit;

	hit.hit = 0;
	hit.dist = 0;
	hit.x = 0.0;
	hit.y = 0.0;
	hit.side = 1;
	hit.wall = 0.0;
	init_cast_horizontal(d, angle, &cast);
	if (cast.dir_y > -0.000001 && cast.dir_y < 0.000001)
		return (hit);
	while (cast.depth < cast.max_depth && hit.hit == 0)
	{
		if (is_wall_at(d, cast.x, cast.y))
			fill_hit_from_cast(&hit, &cast, 1);
		else
			step_cast(&cast);
	}
	return (hit);
}

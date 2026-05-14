/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abollia <abollia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 11:25:07 by asdiallo          #+#    #+#             */
/*   Updated: 2025/12/19 14:07:09 by abollia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	key_init(t_data *d)
{
	d->keys.w = 0;
	d->keys.a = 0;
	d->keys.s = 0;
	d->keys.d = 0;
	d->keys.left = 0;
	d->keys.right = 0;
}

int	key_press(int keycode, t_data *data)
{
	if (keycode == KEY_W)
		data->keys.w = 1;
	else if (keycode == KEY_A)
		data->keys.a = 1;
	else if (keycode == KEY_S)
		data->keys.s = 1;
	else if (keycode == KEY_D)
		data->keys.d = 1;
	else if (keycode == KEY_LEFT)
		data->keys.left = 1;
	else if (keycode == KEY_RIGHT)
		data->keys.right = 1;
	else if (keycode == KEY_ESC)
		cb_exithub(0, data);
	return (0);
}

int	key_release(int keycode, t_data *data)
{
	if (keycode == KEY_W)
		data->keys.w = 0;
	else if (keycode == KEY_A)
		data->keys.a = 0;
	else if (keycode == KEY_S)
		data->keys.s = 0;
	else if (keycode == KEY_D)
		data->keys.d = 0;
	else if (keycode == KEY_LEFT)
		data->keys.left = 0;
	else if (keycode == KEY_RIGHT)
		data->keys.right = 0;
	return (0);
}

static void	move(t_data *d, double *dx, double *dy)
{
	double	move_speed;
	double	dir;

	move_speed = d->player.speed;
	dir = d->player.dir;
	if (d->keys.w)
	{
		*dx += cos(dir) * move_speed;
		*dy -= sin(dir) * move_speed;
	}
	if (d->keys.s)
	{
		*dx -= cos(dir) * move_speed;
		*dy += sin(dir) * move_speed;
	}
	if (d->keys.a)
	{
		*dx -= sin(dir) * move_speed;
		*dy -= cos(dir) * move_speed;
	}
	if (d->keys.d)
	{
		*dx += sin(dir) * move_speed;
		*dy += cos(dir) * move_speed;
	}
}

//appliquer mouvement a chaque frame
int	update(t_data *data)
{
	double	rot_speed;
	double	dx;
	double	dy;
	double	nx;
	double	ny;

	rot_speed = data->player.rot_speed;
	dx = 0.0;
	dy = 0.0;
	move(data, &dx, &dy);
	ny = data->player.y + dy;
	nx = data->player.x + dx;
	if (!point_hits(data, nx, data->player.y))
		data->player.x = nx;
	if (!point_hits(data, data->player.x, ny))
		data->player.y = ny;
	if (data->keys.left)
		data->player.dir += rot_speed;
	if (data->keys.right)
		data->player.dir -= rot_speed;
	return (0);
}

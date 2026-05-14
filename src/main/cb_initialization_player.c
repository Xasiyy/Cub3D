/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cb_initialization_player.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abollia <abollia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 15:43:00 by asdiallo          #+#    #+#             */
/*   Updated: 2025/12/18 10:04:09 by abollia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	initialization_player(t_data *d)
{
	d->player.x = d->cub->p_x + 0.5;
	d->player.y = d->cub->p_y + 0.5;
	if (d->cub->p_or == 'E')
		d->player.dir = 0.0;
	else if (d->cub->p_or == 'N')
		d->player.dir = MY_HALF_PI;
	else if (d->cub->p_or == 'W')
		d->player.dir = MY_PI;
	else if (d->cub->p_or == 'S')
		d->player.dir = 3.0 * MY_HALF_PI;
	else
	{
		d->player.dir = 0.0;
	}
	d->player.speed = 0.055;
	d->player.rot_speed = 0.055;
	d->player.radius = 0.05;
}

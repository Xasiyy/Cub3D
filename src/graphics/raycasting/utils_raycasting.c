/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_raycasting.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abollia <abollia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 09:53:57 by asdiallo          #+#    #+#             */
/*   Updated: 2025/12/19 14:07:31 by abollia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	step_cast(t_cast *cast)
{
	cast->x += cast->step_x;
	cast->y += cast->step_y;
	cast->depth++;
}

int	is_wall_at(t_data *d, double wx, double wy)
{
	int	row;
	int	col;

	row = (int)wy;
	col = (int)wx;
	return (is_wall(d, row, col));
}

double	apply_fisheye(double raw_dist, double ray_angle, double player_dir)
{
	double	angle_diff;
	double	corrected;

	angle_diff = ray_angle - player_dir;
	corrected = raw_dist * cos(angle_diff);
	return (corrected);
}

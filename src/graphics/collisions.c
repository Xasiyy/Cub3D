/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collisions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abollia <abollia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 23:50:38 by asdiallo          #+#    #+#             */
/*   Updated: 2025/12/17 11:23:18 by abollia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	is_wall(t_data *d, int row, int col)
{
	if (row < 0 || col < 0)
		return (1);
	if (row >= d->cub->m_height || col >= d->cub->m_width)
		return (1);
	if (d->cub->m_pat[row] == NULL)
		return (1);
	if (d->cub->m_pat[row][col] == '\0')
		return (1);
	if (d->cub->m_pat[row][col] == '1')
		return (1);
	if (d->cub->m_pat[row][col] == ' ')
		return (1);
	return (0);
}

static t_bbox	init_bbox(double x, double y, double r)
{
	t_bbox	box;

	box.row_max = (int)floor(y + r);
	box.row_min = (int)floor(y - r);
	box.col_max = (int)floor(x + r);
	box.col_min = (int)floor(x - r);
	return (box);
}

int	point_hits(t_data *d, double x, double y)
{
	t_bbox			box;
	int				row;
	int				col;

	box = init_bbox(x, y, d->player.radius);
	row = box.row_min;
	while (row <= box.row_max)
	{
		col = box.col_min;
		while (col <= box.col_max)
		{
			if (is_wall(d, row, col))
				return (1);
			col++;
		}
		row++;
	}
	return (0);
}

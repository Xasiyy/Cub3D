/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abollia <abollia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 14:19:05 by asdiallo          #+#    #+#             */
/*   Updated: 2025/12/19 14:06:59 by abollia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	my_pixel_put(t_img *img, int x, int y, unsigned int color)
{
	char	*dst;
	int		offset;

	if (x < 0 || y < 0 || x >= img->width || y >= img->height)
		return ;
	offset = y * img->line_len + x * (img->bpp / 8);
	dst = img->addr + offset;
	*(unsigned int *)dst = color;
}

static unsigned int	cell_color(char c)
{
	if (c == '1')
		return (0x00999999);
	if (c == '2')
		return (0x00CC3333);
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
		return (0x001A1A1A);
	if (c == '0')
		return (0x001A1A1A);
	return (0x00000000);
}

static void	draw_minimap_row(t_data *d, int y, t_point off, int tile)
{
	char	*line;
	char	c;
	int		x;
	int		len;
	t_point	pos;

	line = d->map->pattern[y];
	len = 0;
	if (line)
		len = ft_strlen(line);
	x = 0;
	while (x < d->cub->m_width)
	{
		if (line && x < len)
			c = line[x];
		else
			c = ' ';
		if (c != ' ')
		{
			pos.x = off.x + x * tile;
			pos.y = off.y + y * tile;
			draw_tile_mm(&d->img, pos, tile, cell_color(c));
		}
		x++;
	}
}

void	draw_minimap(t_data *d)
{
	t_point	offset;
	int		tile;
	int		y;

	mm_setup(d, &offset.x, &offset.y, &tile);
	y = 0;
	while (y < d->cub->m_height)
	{
		draw_minimap_row(d, y, offset, tile);
		y++;
	}
	draw_player(d, offset.x, offset.y, tile);
}

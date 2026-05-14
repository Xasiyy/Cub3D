/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_graphics.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asdiallo <asiya040906@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 16:12:35 by asdiallo          #+#    #+#             */
/*   Updated: 2025/11/26 11:35:30 by asdiallo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	init_graphics(t_data *data)
{
	int	sw;
	int	sh;

	data->mlx = mlx_init();
	if (!data->mlx)
		cb_errorhub("MLX init failed", 1, data);
	mlx_get_screen_size(data->mlx, &sw, &sh);
	if (!data->mlx)
		cb_errorhub(":LX init failed", 1, data);
	data->win_w = WIN_W;
	data->win_h = WIN_H;
	data->win = mlx_new_window(data->mlx, data->win_w, data->win_h, "Cub3d");
	if (!data->win)
		cb_errorhub("Window creation failed", 1, data);
	data->img.ptr = mlx_new_image(data->mlx, data->win_w, data->win_h);
	if (!data->img.ptr)
		cb_errorhub("Image creation failed", 1, data);
	data->img.addr = mlx_get_data_addr(data->img.ptr,
			&data->img.bpp,
			&data->img.line_len,
			&data->img.endian);
	data->img.width = data->win_w;
	data->img.height = data->win_h;
	load_all_textures(data);
	init_rays(data);
}

int	handle_keypress(int keycode, t_data *d)
{
	if (keycode == KEY_ESC)
		close_window(d);
	return (0);
}

int	close_window(t_data *d)
{
	cb_exithub(0, d);
	return (0);
}

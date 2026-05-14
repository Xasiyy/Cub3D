/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cb_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asdiallo <asiya040906@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 15:36:41 by abollia           #+#    #+#             */
/*   Updated: 2025/12/11 12:06:31 by asdiallo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	main(int ac, char **av)
{
	t_data	d;

	gc_init(&d);
	cb_initialization(&d);
	cb_parser(ac, av, &d);
	if (!d.cub->m_pat)
		cb_errorhub("Map pattern missing", 1, &d);
	d.map->pattern = d.cub->m_pat;
	key_init(&d);
	initialization_player(&d);
	init_graphics(&d);
	draw_minimap(&d);
	mlx_put_image_to_window(d.mlx, d.win, d.img.ptr, 0, 0);
	mlx_hook(d.win, 2, 1L << 0, key_press, &d);
	mlx_hook(d.win, 3, 1L << 1, key_release, &d);
	mlx_hook(d.win, 17, 0, close_window, &d);
	mlx_loop_hook(d.mlx, render_frame, &d);
	mlx_loop(d.mlx);
	cb_exithub(0, &d);
}

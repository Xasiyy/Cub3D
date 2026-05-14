/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cb_pars_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abollia <abollia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 16:07:30 by abollia           #+#    #+#             */
/*   Updated: 2025/12/18 09:44:21 by abollia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static bool	cb_pars_map_iv_verifyer(char **map, int y, int x, char *ex)
{
	if (!ft_strchr(ex, map[y][x + 1]) || map[y][x + 1] == 0)
		return (false);
	else if (!ft_strchr(ex, map[y][x - 1]) || map[y][x - 1] == 0)
		return (false);
	else if (!ft_strchr(ex, map[y + 1][x]) || map[y + 1][x] == 0)
		return (false);
	else if (!ft_strchr(ex, map[y - 1][x]) || map[y - 1][x] == 0)
		return (false);
	else
		return (true);
}

static void	cb_pars_map_isvalid(char **map, int *n_play, int y, t_cub *c)
{
	int	x;

	x = -1;
	while (map[y][++x])
	{
		if (map[y][x] != '0' && map[y][x] != '1' && map[y][x] != 'N'
			&& map[y][x] != 'S' && map[y][x] != 'W' && map[y][x] != 'E'
			&& map[y][x] != ' ' && map[y][x] != '\n')
			cb_errorhub(ERR_MAP_INV, 1, c->data);
		if (map[y][x] == 'N' || map[y][x] == 'S'
			|| map[y][x] == 'W' || map[y][x] == 'E')
		{
			c->p_or = map[y][x];
			c->p_x = (double)x;
			c->p_y = (double)y;
			(*n_play)++;
			if (!cb_pars_map_iv_verifyer(map, y, x, "01"))
				cb_errorhub(ERR_P_POS, 1, c->data);
		}
	}
}

static void	cb_pars_map_isclosed(char **map, int y, t_cub *c)
{
	int	x;

	x = -1;
	while (map[y][++x])
	{
		if (map[y][x] == '0')
			if (!cb_pars_map_iv_verifyer(map, y, x, "01NSWE"))
				cb_errorhub(ERR_MAP_CLO, 1, c->data);
	}
}

void	cb_pars_map(t_cub *c)
{
	int	y;
	int	n_play;

	y = -1;
	n_play = 0;
	while (c->m_pat[++y])
		cb_pars_map_isvalid(c->m_pat, &n_play, y, c);
	y = -1;
	while (c->m_pat[++y])
		cb_pars_map_isclosed(c->m_pat, y, c);
	if (n_play != 1)
		cb_errorhub(ERR_P_NB, 1, c->data);
}

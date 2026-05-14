/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cb_pars_pc_extractors.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abollia <abollia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 18:28:51 by abollia           #+#    #+#             */
/*   Updated: 2025/12/18 12:50:33 by abollia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

char	*cb_pars_pc_dsp_extracttex(char *line, int *i, t_cub *c)
{
	char	*path;
	int		fd;

	(*i) += 2;
	while (line[*i] == ' ')
		(*i)++;
	path = cb_strtrim(&line[*i], "\n", c->data);
	if (!path)
		cb_errorhub(ERR_MALLOC, 1, c->data);
	if (ft_filecheck(path, ".xpm"))
	{
		cb_errorhub(ERR_TEX_EXT, 1, c->data);
	}
	fd = open(path, O_RDONLY);
	if (fd == -1)
	{
		cb_errorhub(ERR_TEX_ACC, 1, c->data);
	}
	close(fd);
	return (path);
}

static bool	cb_pars_pc_iscolorvalid(char *s, char **col)
{
	int	i;
	int	tmp;

	i = -1;
	while (s[++i])
	{
		if (!ft_isdigit(s[i]) && !ft_isspace(s[i]) && s[i] != ',')
			return (false);
	}
	i = -1;
	while (col[++i])
	{
		tmp = ft_atoi(col[i]);
		if (!(0 <= tmp && tmp <= 255))
			return (false);
	}
	if (i != 3)
		return (false);
	return (true);
}

void	cb_pars_pc_dsp_extractcol(char *line, int code, t_cub *c)
{
	int		i;
	int		j;
	char	**col;

	i = 1;
	while (line[i] == ' ')
		i++;
	col = ft_split(&line[i], ',');
	if (!cb_pars_pc_iscolorvalid(&line[i], col))
	{
		ft_ffa(&col);
		cb_errorhub(ERR_COL, 1, c->data);
	}
	j = -1;
	if (code)
	{
		while (col[++j])
			c->f_col[j] = ft_atoi(col[j]);
	}
	else
	{
		while (col[++j])
			c->c_col[j] = ft_atoi(col[j]);
	}
	ft_ffa(&col);
}

static void	cb_pars_map_rectangulizer(t_cub *c)
{
	int		y;
	int		x;
	char	**tmp;

	tmp = gc_malloc(c->data, sizeof(char *) * (c->m_height + 1));
	y = -1;
	while (++y < c->m_height)
	{
		tmp[y] = gc_malloc(c->data, sizeof(char) * (c->m_width + 1));
		ft_memset(tmp[y], ' ', c->m_width);
		tmp[y][c->m_width] = '\0';
	}
	tmp[c->m_height] = NULL;
	y = -1;
	while (c->m_pat[++y])
	{
		x = -1;
		while (c->m_pat[y][++x])
			tmp[y + 1][x + 1] = c->m_pat[y][x];
	}
	ft_ffa(&c->m_pat);
	c->m_pat = tmp;
}

void	cb_pars_pc_extractmap(char **content, t_cub *c)
{
	int	i;
	int	len;

	i = 0;
	while (content[i] && !ft_isonlyspace(content[i]))
		i++;
	c->m_height = i + 2;
	c->m_pat = (char **)cb_secumalloc(sizeof(char *) * (i + 1), c->data);
	i = -1;
	while (content[++i])
	{
		if (ft_isonlyspace(content[i]))
			break ;
		len = ft_strlen(content[i]);
		c->m_pat[i] = ft_strtrim(content[i], "\n");
		if (!c->m_pat[i])
			cb_errorhub(ERR_MALLOC, 1, c->data);
		if (c->m_width < len + 2)
			c->m_width = len + 2;
	}
	c->m_pat[i] = NULL;
	cb_pars_map_rectangulizer(c);
	if (!c)
		return ;
}

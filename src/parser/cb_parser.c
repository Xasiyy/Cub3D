/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cb_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abollia <abollia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 16:32:34 by abollia           #+#    #+#             */
/*   Updated: 2025/12/18 10:28:04 by abollia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static bool	cb_pars_pc_dispatch(char *line, t_cub *c)
{
	int	i;

	i = 0;
	while (line[i] == ' ')
		i++;
	if (!ft_strncmp("NO", &line[i], 2))
		c->n_tex = cb_pars_pc_dsp_extracttex(line, &i, c);
	else if (!ft_strncmp("SO", &line[i], 2))
		c->s_tex = cb_pars_pc_dsp_extracttex(line, &i, c);
	else if (!ft_strncmp("WE", &line[i], 2))
		c->w_tex = cb_pars_pc_dsp_extracttex(line, &i, c);
	else if (!ft_strncmp("EA", &line[i], 2))
		c->e_tex = cb_pars_pc_dsp_extracttex(line, &i, c);
	else if (!ft_strncmp("F", &line[i], 1))
		cb_pars_pc_dsp_extractcol(&line[i], 1, c);
	else if (!ft_strncmp("C", &line[i], 1))
		cb_pars_pc_dsp_extractcol(&line[i], 0, c);
	else if (ft_strchr("01NSWE", line[i]))
		return (false);
	else
		cb_errorhub("Unknown key", 1, c->data);
	return (true);
}

static void	cb_pars_parscontent(t_file *f, t_data *d)
{
	int	i;

	cb_pars_pc_checkduplicate(f->content, d->pars);
	i = -1;
	while (f->content[++i])
	{
		if (ft_isonlyspace(f->content[i]))
			i++;
		if (!cb_pars_pc_dispatch(f->content[i], d->cub))
			break ;
	}
	cb_pars_pc_extractmap(&f->content[i], d->cub);
}

static void	cb_pars_convertcolors(t_cub *c)
{
	c->c_int_col = ((255 << 24) | (c->c_col[0] << 16)
			| (c->c_col[1] << 8) | c->c_col[2]);
	c->f_int_col = ((255 << 24) | (c->f_col[0] << 16)
			| (c->f_col[1] << 8) | c->f_col[2]);
}

void	cb_parser(int ac, char **av, t_data *d)
{
	if (ac != 2)
		cb_errorhub(ERR_ARG, 1, d);
	if (ft_filecheck(av[1], ".cub"))
		cb_errorhub(ERR_FILE, 1, d);
	cb_pars_storefile(av[1], d->file, d);
	cb_pars_parscontent(d->file, d);
	cb_pars_convertcolors(d->cub);
	cb_pars_map(d->cub);
}

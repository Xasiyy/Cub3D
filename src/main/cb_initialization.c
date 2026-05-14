/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cb_initialization.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abollia <abollia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 13:41:16 by abollia           #+#    #+#             */
/*   Updated: 2025/12/17 10:26:21 by abollia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	cb_ini_cub(t_cub *cub, t_data *d)
{
	cub->n_tex = NULL;
	cub->s_tex = NULL;
	cub->w_tex = NULL;
	cub->e_tex = NULL;
	cub->f_col[0] = 0;
	cub->f_col[1] = 0;
	cub->f_col[2] = 0;
	cub->f_col[3] = 255;
	cub->c_col[0] = 0;
	cub->c_col[1] = 0;
	cub->c_col[2] = 0;
	cub->c_col[3] = 255;
	cub->f_int_col = 0;
	cub->c_int_col = 0;
	cub->m_pat = NULL;
	cub->m_width = 0;
	cub->m_height = 0;
	cub->p_or = 0;
	cub->p_x = 0;
	cub->p_y = 0;
	cub->data = d;
}

static void	cb_ini_pars(t_pars *pars, t_data *d)
{
	pars->nb_n = 0;
	pars->nb_s = 0;
	pars->nb_w = 0;
	pars->nb_e = 0;
	pars->nb_f = 0;
	pars->nb_c = 0;
	pars->nb_map = 0;
	pars->data = d;
}

static void	cb_ini_file(t_file *f, t_data *d)
{
	f->fd = -1;
	f->lcount = 0;
	f->content = NULL;
	f->data = d;
}

void	cb_initialization(t_data *d)
{
	d->file = (t_file *)gc_malloc(d, sizeof(t_file));
	cb_ini_file(d->file, d);
	d->pars = (t_pars *)gc_malloc(d, sizeof(t_pars));
	cb_ini_pars(d->pars, d);
	d->cub = (t_cub *)gc_malloc(d, sizeof(t_cub));
	cb_ini_cub(d->cub, d);
	d->map = (t_map *)gc_malloc(d, sizeof(t_map));
}

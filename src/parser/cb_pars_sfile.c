/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cb_pars_sfile.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abollia <abollia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 12:58:51 by abollia           #+#    #+#             */
/*   Updated: 2025/12/16 23:22:13 by abollia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	cb_pars_sfile_open(char *file, t_file *f)
{
	char	*path;

	path = cb_strdup(file, f->data);
	if (!path)
		cb_errorhub(ERR_MALLOC, 1, f->data);
	f->fd = open(path, O_RDONLY);
	if (f->fd == -1)
		cb_errorhub(ERR_ACC, 1, f->data);
}

static size_t	cb_pars_sfile_lcount(t_data *d)
{
	int		fd;
	char	*line;
	size_t	lcount;

	fd = d->file->fd;
	lcount = 0;
	line = get_next_line(fd);
	while (line)
	{
		lcount++;
		free(line);
		line = get_next_line(fd);
	}
	if (!lcount)
		cb_errorhub("Empty file", 1, d);
	return (lcount);
}

void	cb_pars_storefile(char *file, t_file *f, t_data *d)
{
	int		i;
	char	*line;

	cb_pars_sfile_open(file, f);
	f->lcount = cb_pars_sfile_lcount(d);
	close(f->fd);
	cb_pars_sfile_open(file, f);
	f->content = (char **)gc_malloc(d, sizeof(char *) * (f->lcount + 1));
	line = get_next_line(f->fd);
	i = 0;
	while (line)
	{
		f->content[i] = cb_strdup(line, d);
		if (!f->content[i])
			cb_errorhub(ERR_MALLOC, 1, d);
		i++;
		free(line);
		line = get_next_line(f->fd);
	}
	f->content[i] = NULL;
	close(f->fd);
}

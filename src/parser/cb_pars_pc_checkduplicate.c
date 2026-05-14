/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cb_pars_pc_checkduplicate.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abollia <abollia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/26 20:54:08 by abollia           #+#    #+#             */
/*   Updated: 2025/12/16 23:05:21 by abollia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static bool	cb_pars_pc_cd_incrementor(char *line, t_pars *p)
{
	int	i;

	i = 0;
	while (line[i] == ' ')
		i++;
	if (!ft_strncmp("NO", &line[i], 2))
		p->nb_n++;
	else if (!ft_strncmp("SO", &line[i], 2))
		p->nb_s++;
	else if (!ft_strncmp("WE", &line[i], 2))
		p->nb_w++;
	else if (!ft_strncmp("EA", &line[i], 2))
		p->nb_e++;
	else if (!ft_strncmp("F", &line[i], 1))
		p->nb_f++;
	else if (!ft_strncmp("C", &line[i], 1))
		p->nb_c++;
	else if (!ft_strncmp("1", &line[i], 1))
	{
		p->nb_map++;
		return (false);
	}
	return (true);
}

void	cb_pars_pc_checkduplicate(char **content, t_pars *p)
{
	int	i;

	i = -1;
	while (content[++i])
	{
		if (!cb_pars_pc_cd_incrementor(content[i], p))
			break ;
	}
	if (p->nb_n > 1 || p->nb_s > 1 || p->nb_w > 1 || p->nb_e > 1
		|| p->nb_f > 1 || p->nb_c > 1)
		cb_errorhub(ERR_CDUP, 1, p->data);
	else if (!p->nb_n || !p->nb_s || !p->nb_w || !p->nb_e
		|| !p->nb_f || !p->nb_c || !p->nb_map)
		cb_errorhub(ERR_MISS, 1, p->data);
}

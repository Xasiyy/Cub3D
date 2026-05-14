/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asdiallo <asiya040906@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 12:01:14 by asdiallo          #+#    #+#             */
/*   Updated: 2025/12/11 12:02:09 by asdiallo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	gc_init(t_data *d)
{
	d->gc = NULL;
}

void	gc_remove(t_data *d, void *ptr)
{
	t_gc	*cur;
	t_gc	*prev;

	prev = NULL;
	cur = d->gc;
	while (cur)
	{
		if (cur->ptr == ptr)
		{
			if (prev)
				prev->next = cur->next;
			else
				d->gc = cur->next;
			free(cur);
			return ;
		}
		prev = cur;
		cur = cur->next;
	}
}

//save ptr in gc
void	gc_add(t_data *d, void *ptr)
{
	t_gc	*node;

	if (!ptr)
		return ;
	node = cb_secumalloc(sizeof(t_gc), d);
	if (!node)
		cb_errorhub("malloc failed in gc_add", 1, d);
	node->ptr = ptr;
	node->next = d->gc;
	d->gc = node;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asdiallo <asiya040906@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/15 09:41:11 by asdiallo          #+#    #+#             */
/*   Updated: 2025/12/11 12:01:55 by asdiallo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	*gc_malloc(t_data *d, ssize_t size)
{
	void	*ptr;

	ptr = cb_secumalloc(size, d);
	if (!ptr)
		cb_errorhub("malloc failed in gc_malloc", 1, d);
	gc_add(d, ptr);
	return (ptr);
}

void	gc_free_one(t_data *d, void *ptr)
{
	t_gc	*cur;
	t_gc	*prev;

	prev = NULL;
	cur = d->gc;
	while (cur->ptr == ptr)
	{
		if (prev)
			prev->next = cur->next;
		else
			d->gc = cur->next;
		free(cur->ptr);
		free(cur);
		return ;
	}
	prev = cur;
	cur = cur->next;
}

void	gc_free_all(t_data *d)
{
	t_gc	*cur;
	t_gc	*next;

	cur = d->gc;
	while (cur)
	{
		next = cur->next;
		free(cur->ptr);
		free(cur);
		cur = next;
	}
	d->gc = NULL;
}

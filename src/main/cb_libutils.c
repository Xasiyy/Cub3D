/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cb_libutils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abollia <abollia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 11:43:06 by abollia           #+#    #+#             */
/*   Updated: 2025/12/10 11:50:51 by abollia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

char	*cb_strdup(const char *s, t_data *d)
{
	char	*copy;
	size_t	i;
	size_t	len;

	len = ft_strlen(s);
	copy = (char *) gc_malloc(d, sizeof(char) * (len + 1));
	if (copy == NULL)
		return (NULL);
	i = 0;
	while (i < len)
	{
		copy[i] = s[i];
		i++;
	}
	copy[i] = '\0';
	return (copy);
}

static void	*cb_calloc(size_t nmemb, size_t size, t_data *d)
{
	void	*blok;
	size_t	totsize;

	totsize = nmemb * size;
	if (nmemb != 0 && totsize / nmemb != size)
		return (NULL);
	blok = (void *)gc_malloc(d, totsize);
	if (blok == NULL)
		return (NULL);
	ft_bzero(blok, nmemb * size);
	return (blok);
}

static char	*cb_substr(const char *s, unsigned int start, size_t l, t_data *d)
{
	size_t	i;
	size_t	lens;
	char	*zub;

	if (!s)
		return (NULL);
	lens = ft_strlen(s);
	if (start >= lens)
		return (cb_calloc(1, sizeof(char), d));
	if (l > lens - start)
		l = lens - start;
	zub = cb_calloc(l + 1, sizeof(char), d);
	if (!zub)
		return (NULL);
	i = 0;
	while (i < l && s[start + i])
	{
		zub[i] = s[start + i];
		i++;
	}
	zub[i] = '\0';
	return (zub);
}

char	*cb_strtrim(const char *s1, const char *set, t_data *d)
{
	char	*res;
	size_t	start;
	size_t	end;

	if (!s1)
		return (NULL);
	if (!set)
		return (cb_strdup(s1, d));
	start = 0;
	end = ft_strlen(s1) - 1;
	while (s1[start] && ft_strchr(set, s1[start]))
		start++;
	while (s1[end] > 0 && ft_strrchr(set, s1[end]))
		end--;
	res = cb_substr(s1, start, (end - start + 1), d);
	return (res);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abollia <abollia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 16:02:07 by abollia           #+#    #+#             */
/*   Updated: 2025/05/08 15:25:44 by abollia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_wcnt(const char *str, char sep)
{
	int	trigg;
	int	cnt;

	trigg = 0;
	cnt = 0;
	while (*str)
	{
		if (*str != sep && trigg == 0)
		{
			trigg = 1;
			cnt++;
		}
		else if (*str == sep)
			trigg = 0;
		str++;
	}
	return ((size_t)cnt);
}

static int	ft_subdup(const char *str, char **tab, char sep)
{
	size_t	wlen;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (i < ft_wcnt(str, sep))
	{
		if (str[j] != sep)
		{
			wlen = 0;
			while (str[j + wlen] != sep && str[j + wlen])
				wlen++;
			tab[i] = ft_substr(str, j, wlen);
			if (!tab[i])
				return (ft_ffa(&tab), 0);
			i++;
			j += wlen;
		}
		else
			j++;
	}
	tab[i] = NULL;
	return (1);
}

char	**ft_split(const char *s, char c)
{
	char	**tab;
	size_t	wds;

	if (!s)
		return (NULL);
	wds = ft_wcnt(s, c);
	tab = (char **)malloc((wds + 1) * sizeof(char *));
	if (!tab)
		return (NULL);
	if (!ft_subdup(s, tab, c))
		return (NULL);
	return (tab);
}

// int	main(void)
// {
// 	char str1[] = "    beep boop  meep   moop    ";
// 	// char str2[] = "        ";
// 	char **tab;
// 	size_t	i;
// 	i = 0;
// 	tab = ft_split(str1, ' ');
// 	while (tab[i])
// 	{
// 		printf("%s\n", tab[i]);
// 		i++;
// 	}
// 	// if (tab != (void *)0)
// 	// 	ft_ffa(tab);
// 	i = 0;
// 	while (i < 4)
// 	{
// 		free(tab[i]);
// 		i++;
// 	}
// 	free(tab);
// 	return (0);
// }

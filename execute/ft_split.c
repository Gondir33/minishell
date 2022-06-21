/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbendu <sbendu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 21:09:48 by sbendu            #+#    #+#             */
/*   Updated: 2022/06/21 08:58:26 by sbendu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

char	**ft_tabfree(char	**tab)
{
	size_t	i;

	i = 0;
	if (tab)
	{
		while (tab[i])
		{
			free(tab[i]);
			i++;
		}
		free(tab);
	}
	return (NULL);
}

static size_t	ft_row(char const *s, char c)
{
	size_t	i;
	size_t	row;

	i = 0;
	row = 0;
	while (s[i])
	{
		if ((s[i] != c && s[i + 1] && s[i + 1] == c)
			|| (s[i] != c && !s[i + 1]))
			row++;
		i++;
	}
	return (row);
}

static char	**tabmalloc(char const *s, char c)
{
	char	**tab;
	size_t	i;
	size_t	j;
	size_t	len;

	i = 0;
	len = ft_row(s, c);
	tab = malloc(sizeof(char *) * (len + 1));
	if (tab == NULL)
		return (NULL);
	while (i++ < len)
	{
		j = 0;
		while (*s == c)
			s++;
		while (*s != c && *s != 0)
		{
			s++;
			j++;
		}
		tab[i - 1] = malloc(sizeof(char) * (j + 1));
		if (tab[i - 1] == NULL)
			return (ft_tabfree(tab));
	}
	return (tab);
}

static char	**tabfill(char const *s, char c, char **tab)
{
	size_t	i;
	size_t	j;
	size_t	k;

	i = 0;
	k = 0;
	while (s[i])
	{
		j = 0;
		while (s[i] == c)
			i++;
		if (!s[i])
			break ;
		while (s[i] != c && s[i] != 0)
			tab[k][j++] = s[i++];
		tab[k][j] = 0;
		k++;
	}
	tab[k] = NULL;
	return (tab);
}

char	**ft_split(char const *s, char c)
{
	char	**tab;

	if (!s)
		return (NULL);
	tab = tabmalloc(s, c);
	if (!tab)
		return (NULL);
	return (tabfill(s, c, tab));
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbendu <sbendu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 21:08:56 by sbendu            #+#    #+#             */
/*   Updated: 2022/06/20 23:14:00 by sbendu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

char	*ft_strdup(char *s)
{
	char	*news;
	size_t	i;
	size_t	len;

	i = 0;
	len = ft_strlen(s);
	news = malloc(len + 1);
	if (!news)
		return (NULL);
	while (i < len + 1)
	{
		news[i] = s[i];
		i++;
	}
	return (news);
}
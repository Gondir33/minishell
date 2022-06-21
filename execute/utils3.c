/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbendu <sbendu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 21:08:56 by sbendu            #+#    #+#             */
/*   Updated: 2022/06/21 13:08:00 by sbendu           ###   ########.fr       */
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

void	get_status(t_info *info, t_execute *cmds)
{
	if (info->status == 2)
		info->status = 130;
	else if (info->status == 3)
		info->status = 131;
	else if (info->status == 65280)
	{
		ft_error(cmds->command, ": command not found");
		info->status = 127;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbendu <sbendu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 15:35:31 by sbendu            #+#    #+#             */
/*   Updated: 2022/06/10 08:52:22 by sbendu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		if (s1[i] != s2[i] || !s1[i] || !s2[i])
			return (((unsigned char *)s1)[i] - ((unsigned char *)s2)[i]);
		i++;
	}
	return (0);
}

char *ft_strjoin2(char *first, char *second)
{
	int	i;
	char *tmp;

	i = 0;
 	tmp = (char *)malloc(ft_strlen(first) + ft_strlen(second) + 1);
	while (first[i])
	{
		tmp[i] = first[i];
		i++;
	}
	while (*second)
	{
		tmp[i] = *second;
		i++;
		second++;
	}
	tmp[i] = 0;
	return (tmp);
}

char	**init_arg(t_execute *cmds, int num)
{
	int 	i;
	char	**arg;

	i = 0;
	arg = (char **)malloc(num + 1);
	arg[i] = ft_strjoin2("/usr/bin/", cmds->command);
	if (cmds->argument->next)
		cmds->argument = cmds->argument->next;
	while (++i < num)
	{
		arg[i] = cmds->argument->argument;
		cmds->argument = cmds->argument->next;
	}
	return (arg);
}
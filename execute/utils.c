/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbendu <sbendu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 12:57:39 by sbendu            #+#    #+#             */
/*   Updated: 2022/06/20 22:31:48 by sbendu           ###   ########.fr       */
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

char	*ft_strjoin2(char *first, char *second)
{
	int		i;
	char	*tmp;

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

void	init_arg(t_execute *cmds, int num)
{
	int		i;
	t_info	*info;
	
	info = cmds->info;
	while (cmds)
	{
		i = 0;
		cmds->arguments = (char **)malloc(sizeof(char **) * (num + 2));
		cmds->arguments[i] = get_cmd(info, cmds->command);
		while (cmds->argument->next)
		{
			cmds->arguments[++i] = cmds->argument->argument;
			cmds->argument = cmds->argument->next;
		}
		cmds->arguments[++i] = cmds->argument->argument;
		cmds->argument = cmds->argument->head;
		cmds->arguments[++i] = NULL;
		cmds = cmds->next;
	}
}

int	ft_lstsize(t_execute *lst)
{
	int	len;

	len = 0;
	while (lst != NULL)
	{
		lst = lst->next;
		++len;
	}
	return (len);
}

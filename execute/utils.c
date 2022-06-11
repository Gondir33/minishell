/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbendu <sbendu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 15:35:31 by sbendu            #+#    #+#             */
/*   Updated: 2022/06/11 15:22:06 by sbendu           ###   ########.fr       */
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

void	init_arg(t_execute *cmds, int num)
{
	int 	i;

	while (cmds)
	{
		i = 0;
		cmds->arguments = (char **)malloc(num + 1);
		cmds->arguments[i] = ft_strjoin2("/usr/bin/", cmds->command);
		++i;
		while (cmds->argument)
		{
			cmds->arguments[i] = cmds->argument->argument;
			cmds->argument = cmds->argument->next;
			++i;
		}
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

int	ft_error(char *cmd, char *mess)
{
	write(2, cmd, ft_strlen(cmd));
	write(2, mess, ft_strlen(mess));
	write(2, "\n", 1);
	return (-1);
}

void fd_close(int fd_0, int fd_1, t_execute *cmds)
{
	if (cmds->stdIn != 0)
		close(fd_0);
	if (cmds->stdOut != 0)
		close(fd_1);
	if (cmds->stdOut2 != 0)
		close(fd_1);
}

int	ft_arg_size(t_arguments *arg)
{
	int	len;

	len = 0;
	while (arg)
	{
		++len;
		arg= arg->next;
	}
	return (len);
}
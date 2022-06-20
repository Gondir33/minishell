/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbendu <sbendu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 00:23:14 by sbendu            #+#    #+#             */
/*   Updated: 2022/06/20 14:12:32 by sbendu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

int	ft_error(char *cmd, char *mess)
{
	write(2, cmd, ft_strlen(cmd));
	write(2, mess, ft_strlen(mess));
	write(2, "\n", 1);
	return (1);
}

void	fd_close(int fd_0, int fd_1, t_execute *cmds)
{
	if (cmds->stdin != 0 || cmds->stdin2 != 0)
		close(fd_0);
	if (cmds->stdout != 0 || cmds->stdout2 != 0)
		close(fd_1);
}

int	ft_arg_size(t_arguments *arg)
{
	int	len;

	len = 0;
	while (arg)
	{
		++len;
		arg = arg->next;
	}
	return (len);
}

void	close_fd_pip(t_pipex *pip)
{
	int	i;

	i = -1;
	while (++i < pip->num_pipes * 2)
		close(pip->pipe_fd[i]);
}

int	init_pip(t_pipex *pip)
{
	int	i;

	i = -1;
	pip->pipe_fd = malloc(sizeof(int) * pip->num_pipes * 2);
	if (!pip->pipe_fd)
		return (1);
	while (++i < pip->num_pipes)
		if (pipe(pip->pipe_fd + i * 2) == -1)
			return (1);
	pip->pid = malloc(sizeof(int) * (pip->num_pipes + 2));
	pip->pid[pip->num_pipes + 1] = 0;
	return (0);
}

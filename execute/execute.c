/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbendu <sbendu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 19:30:59 by sbendu            #+#    #+#             */
/*   Updated: 2022/06/11 16:17:27 by sbendu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

static void child_no_pipe(t_execute *cmds, t_info *info, int *fd)
{
		int	flag;

		flag = 1;
		if (cmds->stdIn != 0)
			dup2(fd[0], 0);
		if (cmds->stdOut != 0)
			dup2(fd[1], 1);
		if (cmds->stdOut2 != 0)
			dup2(fd[1], 1);
			//bultins
		if (flag == 1)
			if (!fork())
			{
				fd_close(fd[0], fd[1], cmds);
				info->status = execve(cmds->arguments[0], cmds->arguments, info->envp);
				exit(info->status);
			}
		fd_close(fd[0], fd[1], cmds);
}

int	no_pipe_exe(t_execute *cmds, t_info *info)
{
	int	fd[2];

	if (cmds->stdIn != 0)
	{
		fd[0] = open(cmds->stdIn, O_RDONLY);
		if (fd[0] < 0)
			return (ft_error(cmds->stdIn, ": No such file or dirctory"));
	}
	if (cmds->stdOut != 0)
		fd[1] = open(cmds->stdOut, O_WRONLY | O_TRUNC | O_CREAT);
	if (cmds->stdOut2 != 0)
		fd[1] = open(cmds->stdOut2, O_WRONLY | O_APPEND | O_CREAT);
	child_no_pipe(cmds, info, fd);
	wait(&info->status);
	if (cmds->stdIn != 0)
		close(fd[0]);
	if (cmds->stdOut != 0)
		close(fd[1]);
	return (info->status);
}



int	execute(t_execute *cmds, t_info *info)
{
	t_pipex	pip;

	pip.temp_0_fd = dup(0);
	pip.temp_1_fd = dup(1);
	pip.num_pipes = ft_lstsize(cmds) - 1;
	init_arg(cmds, ft_arg_size(cmds->argument));
	if (pip.num_pipes == 0)
		info->status = no_pipe_exe(cmds, info);
	else
		info->status = pipex(info, cmds, &pip);
	while(cmds)
	{
		free(cmds->arguments[0]);
		free(cmds->arguments);
		cmds = cmds->next;
	}
	dup2(pip.temp_0_fd, 0);
	dup2(pip.temp_1_fd, 1);
	return (0);
}

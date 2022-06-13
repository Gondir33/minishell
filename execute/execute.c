/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbendu <sbendu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 19:30:59 by sbendu            #+#    #+#             */
/*   Updated: 2022/06/13 17:02:36 by sbendu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

static void child_no_pipe(t_execute *cmds, t_info *info, int *fd, int fd_pipe)
{
		int	flag;

		flag = 1;
		if (cmds->stdIn != 0 )
			dup2(fd[0], 0);
		if (cmds->stdIn2)
			dup2(fd_pipe, 0);
		if (cmds->stdOut != 0 || cmds->stdOut2 != 0)
			dup2(fd[1], 1);
			//bultins
		info->pid_child = (int *)malloc(sizeof(int) * 2);
		if (flag == 1) 
		{
			info->pid_child[0] = fork();
			info->pid_child[1] = 0;
			if (!info->pid_child[0])
			{
				fd_close(fd[0], fd[1], cmds);
				if (cmds->stdIn2)
					close(fd_pipe);
				info->status = execve(cmds->arguments[0], cmds->arguments, info->envp);
				free(info->pid_child);
				exit(info->status);
			}
		}
		fd_close(fd[0], fd[1], cmds);
		if (cmds->stdIn2)
			close(fd_pipe);
}

int	no_pipe_exe(t_execute *cmds, t_info *info)
{
	int	fd[2];
	int	fd_pipe[2];

	if (cmds->stdIn != 0)
	{
		fd[0] = open(cmds->stdIn, O_RDONLY);
		if (fd[0] < 0)
			return (ft_error(cmds->stdIn, ": No such file or dirctory"));
	}
	else if (cmds->stdIn2 != 0)// don't works
	{
		if (pipe(fd_pipe) == -1)
			return (-1);
		if (!fork())
		{
			write(fd_pipe[1], cmds->stdIn2, ft_strlen(cmds->stdIn2));
			close(fd_pipe[1]);
			close(fd_pipe[0]);
			exit(0);
		}
		close(fd_pipe[1]);
		wait(&info->status);
	}
	if (cmds->stdOut != 0)
		fd[1] = open(cmds->stdOut, O_WRONLY | O_TRUNC | O_CREAT);
	else if (cmds->stdOut2 != 0)
		fd[1] = open(cmds->stdOut2, O_WRONLY | O_APPEND | O_CREAT);
	child_no_pipe(cmds, info, fd, fd_pipe[0]);
	wait(&info->status);
	free(info->pid_child);
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
		cmds->arguments = NULL;
		cmds = cmds->next;
	}
	dup2(pip.temp_0_fd, 0);
	dup2(pip.temp_1_fd, 1);
	return (0);
}

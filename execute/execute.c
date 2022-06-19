/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbendu <sbendu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 19:30:59 by sbendu            #+#    #+#             */
/*   Updated: 2022/06/19 10:01:20 by sbendu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

static int	fd_open(int **fd, t_execute *cmds)
{
	if (cmds->stdin != 0)
	{
		(*fd)[0] = open(cmds->stdin, O_RDONLY);
		if ((*fd)[0] < 0)
			return (ft_error(cmds->stdin, ": No such file or directory"));
		if (cmds->stdin != 0)
			dup2((*fd)[0], 0);
	}
	else if (cmds->stdin2 != 0)
	{
		if (pipe(*(fd) + 2) == -1)
			return (-1);
		if (!fork())
		{
			write((*fd)[3], cmds->stdin2, ft_strlen(cmds->stdin2));
			close((*fd)[3]);
			close((*fd)[2]);
			exit(0);
		}
		close((*fd)[3]);
		wait(0);
		dup2((*fd)[2], 0);
	}
	return (0);
}

static void	child_no_pipe(t_execute *cmds, t_info *info, int *fd, int fd_pipe)
{
	int	flag;

	flag = 1;
	if (cmds->stdout != 0 || cmds->stdout2 != 0)
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
			if (cmds->stdin2)
				close(fd_pipe);
			info->status = execve(cmds->arguments[0], \
				cmds->arguments, info->envp);
			free(info->pid_child);
			free_all(cmds);
			exit(info->status);
		}
	}
	fd_close(fd[0], fd[1], cmds);
}

int	no_pipe_exe(t_execute *cmds, t_info *info)
{
	int	*fd;

	fd = (int *)malloc(sizeof(int) * 4);
	if (!fd)
		return (ft_error("Erorr:", "fd_malloc_error"));
	if (fd_open(&fd, cmds) == -1)
		return (-1);
	if (cmds->stdout != 0)
		fd[1] = open(cmds->stdout, O_WRONLY | O_TRUNC | O_CREAT);
	else if (cmds->stdout2 != 0)
		fd[1] = open(cmds->stdout2, O_WRONLY | O_APPEND | O_CREAT);
	child_no_pipe(cmds, info, fd, fd[2]);
	if (cmds->stdin2)
		close(fd[2]);
	wait(&info->status);
	free(info->pid_child);
	free(fd);
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
	// else
	// 	info->status = pipex(info, cmds, &pip);
	dup2(pip.temp_0_fd, 0);
	dup2(pip.temp_1_fd, 1);
	return (0);
}

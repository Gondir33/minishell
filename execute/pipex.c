/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbendu <sbendu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/22 09:43:26 by sbendu            #+#    #+#             */
/*   Updated: 2022/06/21 20:25:23 by sbendu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

static int	fd_open2(t_execute *cmds)
{
	int	fd_pipe[2];
	int	pid;

	if (cmds->stdin2 != 0)
	{
		if (pipe(fd_pipe) == -1)
			return (-1);
		pid = fork();
		if (!pid)
		{
			write(fd_pipe[1], cmds->stdin2, ft_strlen(cmds->stdin2));
			close(fd_pipe[1]);
			close(fd_pipe[0]);
			exit(0);
		}
		close(fd_pipe[1]);
		waitpid(pid, 0, 0);
		dup2(fd_pipe[0], 1);
		close(fd_pipe[0]);
	}
	return (0);
}

static int	fd_open(t_execute *cmds, int fd_0, int fd_1, int **fd)
{
	if (cmds->stdin != 0)
	{
		(*fd)[0] = open(cmds->stdin, O_RDONLY);
		if ((*fd)[0] < 0)
			return (ft_error(cmds->stdin, ": No such file or dirctory"));
		dup2((*fd)[0], 0);
	}
	if (fd_open2(cmds) == -1)
		return (-1);
	else
		dup2(fd_0, 0);
	if (cmds->stdout != 0)
	{
		(*fd)[1] = open(cmds->stdout, O_WRONLY | O_TRUNC | O_CREAT, 0666);
		dup2((*fd)[1], 1);
	}
	else if (cmds->stdout2 != 0)
	{
		(*fd)[1] = open(cmds->stdout2, O_WRONLY | O_APPEND | O_CREAT, 0666);
		dup2((*fd)[1], 1);
	}
	else
		dup2(fd_1, 1);
	return (0);
}

int	child_process(t_execute *cmds, int fd_0, int fd_1, t_pipex *pip)
{
	int	*fd;
	int	status;

	fd = malloc(sizeof(int) * 2);
	if (fd_open(cmds, fd_0, fd_1, &fd) == -1)
		return (-1);
	close_fd_pip(pip);
	fd_close(fd[0], fd[1], cmds);
	free(fd);
	status = ft_builtins(cmds, cmds->info);
	if (status == 6)
	{
		status = execve(cmds->arguments[0], cmds->arguments, pip->info->envp);
		if (status == 65280)
		{
			ft_error(cmds->command, ": command not found");
			status = 127;
		}
	}
	exit(status);
}

void	parent_process(t_execute *cmds, t_pipex *pip)
{
	int	i;

	i = -1;
	while (++i <= pip->num_pipes)
	{
		pip->pid[i] = fork();
		if (pip->pid[i] == -1)
			ft_error("Error: fork mistake", "\n");
		if (!pip->pid[i])
		{
			if (i == 0)
				child_process(cmds, pip->temp_0_fd, \
							pip->pipe_fd[i * 2 + 1], pip);
			else if (i == pip->num_pipes)
				child_process(cmds, pip->pipe_fd[(i - 1) * 2], \
							pip->temp_1_fd, pip);
			else
				child_process(cmds, pip->pipe_fd[(i - 1) * 2], \
							pip->pipe_fd[i * 2 + 1], pip);
		}
		cmds = cmds->next;
	}
}

int	pipex(t_info *info, t_execute *cmds, t_pipex *pip)
{
	int			i;
	t_execute	*tmp;

	i = -1;
	tmp = cmds;
	pip->info = info;
	init_pip(pip);
	info->pid_child = pip->pid;
	parent_process(cmds, pip);
	close_fd_pip(pip);
	while (++i <= pip->num_pipes)
	{
		handle_ctrl_c(5000, info->pid_child);
		waitpid(pip->pid[i], &info->status, 0);
		get_status(info, cmds);
		tmp = tmp->next;
	}
	free(pip->pid);
	pip->pid = NULL;
	free(pip->pipe_fd);
	pip->pipe_fd = NULL;
	return (0);
}

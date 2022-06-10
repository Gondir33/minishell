/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbendu <sbendu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/22 09:43:26 by sbendu            #+#    #+#             */
/*   Updated: 2022/06/10 09:14:02 by sbendu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

static void close_fd(t_pipex *pip)
{
	int	i;

	i = -1;
	while (++i < pip->num_pipes * 2)
		close(pip->pipe_fd[i]);
}

static int	init_pip(t_pipex *pip)
{
	int	i;

	i = -1;
	pip->pipe_fd = malloc(sizeof(int) * pip->num_pipes * 2);
	if (!pip->pipe_fd)
		return (-1);
	while (++i < pip->num_pipes)
		if (pipe(pip->pipe_fd + i * 2) == -1)
		return(-1);
	pip->pid = malloc(sizeof(int) * pip->num_pipes);
}

void	ft_open_fd_in_out(t_execute *cmds, int **fd)
{
	if (cmds->stdIn != 0)
		**fd = open(cmds->stdIn, O_RDONLY);
	if (*fd < 0)
		exit(ft_error(cmds->stdIn, ": No such file or dirctory"));
	if (cmds->stdOut != 0)
		*(*fd + 1) = open(cmds->stdOut, O_WRONLY | O_APPEND | O_CREAT);
}

void	child_in_out(t_info *info, t_execute *cmds, int *fd, t_pipex *pip)
{
	int	flag;
	int	i = -1;
	
	flag = 1;
	ft_open_fd_in_out(cmds, &fd);
	dup2(*fd, 0);
	dup2(*(fd + 1), 1);
	// while (++i < NUM_BUILTNS)
	// {
	// 	if (ft_strncmp(info->reserved_words[i], cmds->command,\
	// 			ft_strlen(info->reserved_words[i])) == 0)
	// 	{
	// 		info->status = (info->builtins[i]cmds, info);//builtins return with status
	// 		flag = 0;
	// 	}
	// }
	close_fd(pip);
	if (flag == 1)
		info->status = execve(cmds->arguments[0], cmds->arguments, info->envp);
	exit(info->status);
}

void	child_process(t_info *info, t_execute *cmds, t_pipex *pip)
{
	int	i;

	i = -1;
	while (++i < pip->num_pipes)
	{	
		pip->pid[i] = fork();
		if (!pip->pid[i])
			child_in_out(info, cmds, pip->pipe_fd + i * 2, pip);
		cmds = cmds->next;
	}
}

int	pipex(t_info *info, t_execute *cmds, t_pipex *pip)
{
	int	i;

	if (init_pip(pip))
		return (-1);
	child_process(info, cmds, pip);
	close_fd(pip);
	i = -1;
	while (++i < pip->num_pipes)
		waitpid(pip->pid[i], &info->status, 0);
	free(pip->pid);
	free(pip->pipe_fd);
}
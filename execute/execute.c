/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbendu <sbendu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 19:30:59 by sbendu            #+#    #+#             */
/*   Updated: 2022/06/10 09:08:42 by sbendu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

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

static void fd_close(int fd_0, int fd_1, t_execute *cmds)
{
	if (cmds->stdIn != 0)
		close(fd_0);
	if (cmds->stdOut != 0 || cmds->stdOut2 != 0)
		close(fd_1);
}

static void child_no_pipe(t_execute *cmds, t_info *info, int *fd)
{
		int	flag;

		flag = 1;
		if (cmds->stdIn != 0)
			dup2(fd[0], 0);
		if (cmds->stdOut != 0 || cmds->stdOut2 != 0)
			dup2(fd[1], 1);
		// while (++i < NUM_BUILTNS)
		// {
		// 	if (ft_strncmp(info->reserved_words[i], cmds->command,\
		// 			ft_strlen(info->reserved_words[i])) == 0)
		// 	{
		// 		info->builtins[i](cmds, info);//builtins return with status
		// 		flag = 0;
		// 	}
		// }
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
	int	i;
	int	fd[2];
	
	i = -1;
	if (cmds->stdIn != 0)
	{
		fd[0] = open(cmds->stdIn, O_RDONLY);
		if (fd[0] < 0)
		return (ft_error(cmds->stdIn, ": No such file or dirctory"));
	}
	if (cmds->stdOut != 0)
		fd[1] = open(cmds->stdIn, O_WRONLY | O_TRUNC | O_CREAT);
	else if (cmds->stdOut2 != 0)
		fd[1] = open(cmds->stdIn2, O_WRONLY | O_APPEND | O_CREAT);
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
	int		temp_0_fd;
	int		temp_1_fd;

	temp_0_fd = dup(0);
	temp_1_fd = dup(1);
	pip.num_pipes = ft_lstsize(cmds) - 1;
	cmds->arguments = init_arg(cmds, pip.num_pipes + 1);
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
	dup2(temp_0_fd, 0);
	dup2(temp_1_fd, 1);
}

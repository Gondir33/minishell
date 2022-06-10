/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbendu <sbendu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 16:53:03 by sbendu            #+#    #+#             */
/*   Updated: 2022/06/10 09:13:05 by sbendu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_H
# define EXECUTE_H

# include "../parser/minishell.h"

//execute
int	execute(t_execute *cmds, t_info *info);

//pwd
char	*ft_pwd();
//pipex
int	ft_error(char *cmd, char *mess);


void	child_in_out(t_info *info, t_execute *cmds, int *fd, t_pipex *pip);
int		pipex(t_info *info, t_execute *cmds, t_pipex *pip);

//builtins
int	echo(t_execute *cmds, t_info *info);
int	pwd(t_execute *cmds, t_info *info);
int ft_arg_len(char **arg);
int	export(t_execute *cmds, t_info *info);

//utils
int	ft_strncmp(const char *s1, const char *s2, size_t n);
char	**init_arg(t_execute *cmds, int num);

#endif
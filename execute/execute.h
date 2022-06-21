/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leldiss <leldiss@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 16:53:03 by sbendu            #+#    #+#             */
/*   Updated: 2022/06/21 17:11:10 by leldiss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_H
# define EXECUTE_H

# include "../pars/minishell.h"

//execute
void	execute(t_execute *cmds, t_info *info);
int		no_pipe_exe(t_execute *cmds, t_info *info);
int		ft_builtins(t_execute *cmds, t_info *info);

//pipex
int		ft_error(char *cmd, char *mess);
void	child_in_out(t_info *info, t_execute *cmds, int *fd, t_pipex *pip);
int		pipex(t_info *info, t_execute *cmds, t_pipex *pip);

//builtins
int		cd(t_execute *cmds, t_info *info);
char	*ft_strrcut(char *arg, char c);
char	*ft_strcut(char *arg, char c);
int		check_key(t_list *lst, char *key, char *value);
int		add_envp(t_list *lst, char *key, char *value);
int		ft_arg_len(char **arg);
int		cd(t_execute *cmds, t_info *info);
int		echo(t_execute *cmds, t_info *info);
int		ft_exit(t_execute *cmds, t_info *info);
int		export(t_execute *cmds, t_info *info);
int		check_valid1(char *arg);
int		check_valid2(char *arg);
int		pwd(t_info *info);
int		unset(t_execute *cmds, t_info *info);
int		check_first(t_info *info, char *key);
int		env(t_info *info);

//utils
int		ft_strncmp(const char *s1, const char *s2, size_t n);
void	init_arg(t_execute *cmds, int num);
char	*ft_strjoin2(char *first, char *second);
int		ft_lstsize(t_execute *lst);
int		ft_error(char *cmd, char *mess);
void	fd_close(int fd_0, int fd_1, t_execute *cmds);
int		ft_arg_size(t_arguments *arg);
void	close_fd_pip(t_pipex *pip);
int		init_pip(t_pipex *pip);
char	**ft_split(char const *s, char c);
char	*ft_strnstr(const char *big, const char *little, size_t len);
char	*get_cmd(t_info *info, char *command);
char	**ft_tabfree(char	**tab);
char	*ft_strdup(char *s);
void	get_status(t_info *info, t_execute *cmds);

//signal
void	make_signals_work(t_info	*info);
void	sighandler(int signal);
void	handle_ctrl_c(int signal, void *ptr);
void	handle_ctrl_qu(int signal, int *ptr);

#endif
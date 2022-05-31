/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbendu <sbendu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 16:53:03 by sbendu            #+#    #+#             */
/*   Updated: 2022/05/31 13:38:47 by sbendu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "libft/libft.h"

#define NUM_BUILTNS 7

typedef struct s_list
{
	char			*value;
	char			*key;
	struct s_list	*next;
}t_list;

typedef struct s_pipex
{
	int num_pipes;
	int	*pipe_fd;
	int	*pid;
}t_pipex;


typedef struct s_execute
{
	char				*command;
	char				*option;
	char				**arguments;
	char				*stdOut;
	char				*stdIn;
	struct s_execute	*next;
}t_execute;

typedef int	(*t_builtin_ptr)(t_execute *, t_info *);

typedef struct s_info
{
	t_builtin_ptr	builtins[NUM_BUILTNS];
	char			reserved_words[NUM_BUILTNS];
	char			**envp;
	t_list			*envp_list;
	char			envp_f;
	char			exit_f;
	int				status;
}t_info;

typedef int	(*t_builtin_ptr)(t_execute *, t_info *);

//pwd
char	*ft_pwd();
//pipex
int	pipex(t_info *info, t_execute *cmds, int num_pipes);

#endif
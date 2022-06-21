/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbendu <sbendu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 20:59:01 by sbendu            #+#    #+#             */
/*   Updated: 2022/06/21 12:53:42 by sbendu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

static char	**take_path(t_list *l_envp)
{
	char	**path;

	path = NULL;
	l_envp = l_envp->head;
	while (l_envp)
	{
		if (!ft_strncmp(l_envp->key, "PATH", ft_strlen(l_envp->key)))
		{
			path = ft_split(l_envp->value, ':');
			break ;
		}
		l_envp = l_envp->next;
	}
	return (path);
}

static char	*check_cmd(char **path, char *tmp_cmd)
{
	int		i;
	char	*tmp;

	i = -1;
	if (path)
	{
		while (path[++i])
		{
			tmp = ft_strjoin2(path[i], tmp_cmd);
			if (access(tmp, F_OK) == 0)
				return (tmp);
			else
				free(tmp);
		}
	}
	return (NULL);
}

char	*get_cmd(t_info *info, char *command)
{
	char	**path;
	char	*tmp_cmd;
	char	*cmd;

	cmd = command;
	path = take_path(info->l_envp);
	tmp_cmd = ft_strjoin2("/", cmd);
	cmd = check_cmd(path, tmp_cmd);
	if (!cmd)
		cmd = ft_strdup(command);
	free(tmp_cmd);
	ft_tabfree(path);
	return (cmd);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbendu <sbendu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 10:53:03 by sbendu            #+#    #+#             */
/*   Updated: 2022/06/20 20:21:56 by sbendu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

int	check_first(t_info *info, char *key)
{
	t_list	*tmp;
	t_list	*head;

	info->l_envp = info->l_envp->head;
	if (ft_strncmp(info->l_envp->key, key, ft_strlen(key)) == 0)
	{
		tmp = info->l_envp;
		info->l_envp = info->l_envp->next;
		head = info->l_envp;
		free(tmp->key);
		free(tmp->value);
		free(tmp);
		while (info->l_envp->next)
		{
			info->l_envp->head = head;
			info->l_envp = info->l_envp->next;
		}
		info->l_envp = info->l_envp->head;
	}
	return (1);
}

static void	check_list(t_info *info, char *key)
{
	t_list	*tmp;

	while (info->l_envp->next)
	{
		if (info->l_envp == info->l_envp->head)
			check_first(info, key);
		else if (ft_strncmp(info->l_envp->next->key, key, ft_strlen(key)) == 0)
		{
			tmp = info->l_envp->next;
			if (info->l_envp->next->next)
				info->l_envp->next = info->l_envp->next->next;
			else
				info->l_envp->next = NULL;
			free(tmp->key);
			free(tmp->value);
			free(tmp);
		}
		if (info->l_envp->next)
			info->l_envp = info->l_envp->next;
	}
}

int	unset(t_execute *cmds, t_info *info)
{
	int		i;

	i = 1;
	while (cmds->arguments[i])
	{
		info->l_envp = info->l_envp->head;
		check_list(info, cmds->arguments[i]);
		i++;
	}
	return (0);
}

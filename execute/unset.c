/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbendu <sbendu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 10:53:03 by sbendu            #+#    #+#             */
/*   Updated: 2022/06/19 15:08:22 by sbendu           ###   ########.fr       */
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

int	unset(t_execute *cmds, t_info *info)
{
	t_list	*tmp;
	char	*key;
	int		i;

	i = 1;
	info->l_envp = info->l_envp->head;
	while (info->l_envp->next)
	{
		if (info->l_envp == info->l_envp->head)
			i += check_first(info, cmds->arguments[i]);
		key = cmds->arguments[i];
		if (ft_strncmp(info->l_envp->next->key, key, ft_strlen(key)) == 0)
		{
			tmp = info->l_envp->next;
			if (info->l_envp->next->next)
				info->l_envp->next = info->l_envp->next->next;
			else
				info->l_envp->next = NULL;
			free(tmp->key);
			free(tmp->value);
			free(tmp);
			++i;
		}
	}
	return (0);
}
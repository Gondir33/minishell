/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbendu <sbendu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 21:03:41 by sbendu            #+#    #+#             */
/*   Updated: 2022/06/21 19:35:22 by sbendu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

int	ft_exit(t_execute *cmds, t_info *info)
{
	int		status;
	t_list	*tmp;

	status = info->status;
	info->l_envp = info->l_envp->head;
	while (info->l_envp)
	{
		tmp = info->l_envp;
		info->l_envp = info->l_envp->next;
		free(tmp->key);
		free(tmp->value);
		free(tmp);
	}
	free_all(cmds);
	exit(status);
}

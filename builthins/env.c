/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbendu <sbendu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 20:59:56 by sbendu            #+#    #+#             */
/*   Updated: 2022/06/10 19:06:36 by sbendu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execute/execute.h"

int	env(t_execute *cmds, t_info *info)
{
	int	i;

	i = -1;
	while (info->envp[++i])
		printf("%s\n", info->envp[i]);
	info->status = 0;
	return (0);
}
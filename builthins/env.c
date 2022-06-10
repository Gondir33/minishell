/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbendu <sbendu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 20:59:56 by sbendu            #+#    #+#             */
/*   Updated: 2022/06/01 09:57:33 by sbendu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	env(t_execute *cmds, t_info *info)
{
	int	i;

	i = -1;
	while (info->envp[++i])
		printf("%s\n", info->envp[i]);
	info->status = 0;
	return (0);
}
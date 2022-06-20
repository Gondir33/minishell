/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbendu <sbendu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 21:03:41 by sbendu            #+#    #+#             */
/*   Updated: 2022/06/20 20:23:44 by sbendu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

int	ft_exit(t_execute *cmds, t_info *info)
{
	int	status;

	status = info->status;
	free_all(cmds);
	exit(status);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbendu <sbendu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 09:38:55 by sbendu            #+#    #+#             */
/*   Updated: 2022/06/21 09:16:07 by sbendu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

int	cd(t_execute *cmds, t_info *info)
{
	int	status;

	if (ft_arg_len(cmds->arguments) > 2)
		return (ft_error("cd: ", "too many arguments"));
	status = chdir(cmds->arguments[1]);
	if (status == -1)
	{
		info->status = 1;
		return (ft_error(cmds->arguments[1], ": No such file or directory"));
	}
	else
		info->status = 0;
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbendu <sbendu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 09:38:55 by sbendu            #+#    #+#             */
/*   Updated: 2022/06/10 19:06:34 by sbendu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execute/execute.h"

int cd(t_execute *cmds, t_info *info)
{
	if (ft_arg_len(cmds->arguments) > 2)
		return (ft_error("cd: ", "too many arguments"));
	info->status = chdir(cmds->arguments[1]);
	if (info->status == -1)
	{
		info->status = 1;
		return (ft_error(cmds->arguments[1], ": No such file or directory"));
	}
}
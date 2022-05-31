/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbendu <sbendu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 20:21:51 by sbendu            #+#    #+#             */
/*   Updated: 2022/05/31 22:13:49 by sbendu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	echo(t_execute *cmds, t_info *info)
{
	int	i;
	int	len;
	
	i = -1;
	len = ft_arg_len(cmds->arguments);
	if (cmds->option == 1)
	{
		while (++i < len - 1)
			printf("%s ", cmds->arguments[i]);
		if (cmds->arguments[i]);
			printf("%s", cmds->arguments[i]);
	}
	else
	{
		while (++i < len - 1)
			printf("%s ", cmds->arguments[i]);
		if (cmds->arguments[i])
			printf("%s", cmds->arguments[i]);
		printf("\n");
	}
}
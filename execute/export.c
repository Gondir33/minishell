/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbendu <sbendu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 12:56:05 by sbendu            #+#    #+#             */
/*   Updated: 2022/06/19 15:07:31 by sbendu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

int check_valid2(char *arg)
{
	int	j;
	int	flag;

	j = 0;
	flag = 0;
	while (arg[++j])
	{
		if (arg[j] == '=')
		{
			flag = 1;
			break ;
		}
	}
	if (flag == 0)
		return (-1);
	while (arg[++j])
		if (arg[j] == '=')
			return (-1);
	return (0);
}

int check_valid1(char *arg)
{
	int	j;

	j = 0;
	while (arg[j] && arg[j] != '=')
	{
		if ((arg[j] >= 'A' && arg[j] <= 'Z') \
		|| (arg[j] >= 'a' && arg[j] <= 'z'))
			return (0);
		j++;
	}
	return (-1);
}

int	export(t_execute *cmds, t_info *info)
{
	int		i;
	char	*key;
	char	*value;

	i = 0;
	while (cmds->arguments[++i])
	{
		if (check_valid1(cmds->arguments[i]) == -1 || check_valid2(cmds->arguments[i]) == -1)
			return (ft_error(cmds->arguments[i], " : not a valid identifier"));
	}
	i = 0;
	while (cmds->arguments[++i])
	{
		key = ft_strcut(cmds->arguments[i], '=');
		value = ft_strrcut(cmds->arguments[i], '=');
		if (check_key(info->l_envp, key, value) == -1)
		{
			if (add_envp(info->l_envp, key, value) == -1)
				return (1);
		}
	}
	info->status = 0;
	return (0);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leldiss <leldiss@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 13:07:37 by leldiss           #+#    #+#             */
/*   Updated: 2022/06/18 13:17:43 by leldiss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	malloc_envp(t_info *info, char *envp)
{
	int	key_size;
	int	value_size;

	key_size = 0;
	value_size = 0;
	while (*envp != '=')
	{
		envp++;
		key_size++;
	}
	envp++;
	while (*envp)
	{
		value_size++;
		envp++;
	}
	info->l_envp->key = malloc(key_size + 1);
	info->l_envp->value = malloc(value_size + 1);
}

int	fill_key(t_info *info, char *envp)
{
	int	index;

	index = 0;
	while (envp[index] != '=')
	{
		info->l_envp->key[index] = envp[index];
		index++;
	}
	info->l_envp->key[index] = 0;
	return (++index);
}

void	fill_value(t_info *info, char *envp, int index)
{
	int	i;

	i = 0;
	while (envp[index])
	{
		info->l_envp->value[i] = envp[index];
		i++;
		index++;
	}
	info->l_envp->value[i] = 0;
}

void	get_envp(t_info *info, char **envp)
{
	int	index;
	int	i;

	i = 1;
	malloc_envp(info, envp[0]);
	index = fill_key(info, envp[0]);
	fill_value(info, envp[0], index);
	while (envp[i] != NULL)
	{
		next_lenvp(info);
		malloc_envp(info, envp[i]);
		index = fill_key(info, envp[i]);
		fill_value(info, envp[i], index);
		i++;
	}
	info->l_envp = info->l_envp->head;
}

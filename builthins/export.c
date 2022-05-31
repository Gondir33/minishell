/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbendu <sbendu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 20:34:29 by sbendu            #+#    #+#             */
/*   Updated: 2022/05/31 20:59:29 by sbendu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_put_last(t_list *envp_l, t_execute *cmds)
{
	while (envp_l)
		envp_l = envp_l->next;
	envp_l = malloc(sizeof(t_list));
	envp_l->key = ft_strchr(s, '=');
	envp_l->value = ft_strrchr(s, '=');
	envp_l->next = NULL;
}

int	export(t_execute *cmds, t_info *info)
{
	int		num_envp;
	int		num_arg;
	char	**new_envp;

	num_envp = ft_arg_len(info->envp);
	num_arg = ft_arg_len(cmds->arguments);
	
}
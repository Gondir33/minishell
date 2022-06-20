/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_structure.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbendu <sbendu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 10:24:52 by leldiss           #+#    #+#             */
/*   Updated: 2022/06/20 22:24:10 by sbendu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_info(t_info *info, char **envp)
{
	info->envp = envp;
	info->status = 0;
	info->l_envp = first_lenvp();
	info->pid_child = NULL;
}

t_execute	*first_execute(void)
{
	t_execute	*tmp;

	tmp = malloc(sizeof(t_execute));
	tmp->head = tmp;
	tmp->next = NULL;
	tmp->argument = NULL;
	tmp->command = NULL;
	tmp->option = NULL;
	tmp->stdin = NULL;
	tmp->stdin2 = NULL;
	tmp->stdout = NULL;
	tmp->stdout2 = NULL;
	tmp->arguments = NULL;
	return (tmp);
}

t_execute	*new_execute(t_execute *info)
{
	t_execute	*tmp;

	tmp = malloc(sizeof(t_execute));
	tmp->head = info->head;
	tmp->next = NULL;
	tmp->argument = NULL;
	tmp->command = NULL;
	tmp->option = NULL;
	tmp->stdin = NULL;
	tmp->stdin2 = NULL;
	tmp->stdout = NULL;
	tmp->stdout2 = NULL;
	info->next = tmp;
	return (tmp);
}

void	first_argument(t_execute *info)
{
	t_arguments	*tmp;

	tmp = malloc(sizeof(t_arguments));
	tmp->head = tmp;
	tmp->next = NULL;
	tmp->argument = NULL;
	info->argument = tmp;
}

void	new_argument(t_execute *info)
{
	t_arguments	*tmp;

	tmp = malloc(sizeof(t_arguments));
	tmp->head = info->argument->head;
	tmp->next = NULL;
	tmp->argument = NULL;
	info->argument->next = tmp;
	info->argument = tmp;
}

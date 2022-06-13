/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_structure.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbendu <sbendu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 10:24:52 by leldiss           #+#    #+#             */
/*   Updated: 2022/06/13 09:55:59 by sbendu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_execute *first_execute(void)
{
	t_execute *tmp;

	tmp = malloc(sizeof(t_execute));
	tmp->head = tmp;
	tmp->next = NULL;
	tmp->argument = NULL;
	tmp->command = NULL;
	tmp->option = NULL;
	tmp->stdIn = NULL;
	tmp->stdIn2 = NULL;
	tmp->stdOut = NULL;
	tmp->stdOut2 = NULL;
	return (tmp);
}

t_execute	*new_execute(t_execute *info)
{
	t_execute *tmp;

	tmp = malloc(sizeof(t_execute));
	tmp->head = info->head;
	tmp->next = NULL;
	tmp->argument = NULL;
	tmp->command = NULL;
	tmp->option = NULL;
	tmp->stdIn = NULL;
	tmp->stdIn2 = NULL;
	tmp->stdOut = NULL;
	tmp->stdOut2 = NULL;
	info->next = tmp;
	return (tmp);
}

void first_argument(t_execute *info)
{
	t_arguments *tmp;

	tmp = malloc(sizeof(t_arguments));
	tmp->head = tmp;
	tmp->next = NULL;
	tmp->argument = NULL;
	info->argument = tmp;
}

void	new_argument(t_execute *info)
{
	t_arguments *tmp;

	tmp = malloc(sizeof(t_arguments));
	tmp->head = info->argument->head;
	tmp->next = NULL;
	tmp->argument = NULL;
	info->argument->next = tmp;
	info->argument = tmp;
}

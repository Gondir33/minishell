/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_structure.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leldiss <leldiss@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 16:19:22 by leldiss           #+#    #+#             */
/*   Updated: 2022/06/18 10:17:57 by leldiss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_arguments(t_arguments *arguments)
{
	t_arguments	*tmp;

	if (arguments->head != NULL)
		arguments = arguments->head;
	while (arguments != NULL)
	{
		tmp = arguments;
		if (arguments->argument != NULL)
			free(arguments->argument);
		arguments = arguments->next;
		free(tmp);
	}
}

void	free_execute(t_execute *info)
{
	t_execute	*tmp;

	if (info->head != NULL)
		info = info->head;
	while (info != NULL)
	{
		tmp = info;
		if (info->arguments != NULL)
		{
			free(info->arguments[0]);
			free(info->arguments);
		}
		if (info->argument != NULL)
			free_arguments(info->argument);
		if (info->command != NULL)
			free(info->command);
		if (info->option != NULL)
			free(info->option);
		if (info->stdin != NULL)
			free(info->stdin);
		if (info->stdin2 != NULL)
			free(info->stdin2);
		if (info->stdout != NULL)
			free(info->stdout);
		if (info->stdout2 != NULL)
			free(info->stdout2);
		info = info->next;
		free(tmp);
	}
}

void	free_all(t_execute *info)
{
	if (info != NULL)
		free_execute(info);
}

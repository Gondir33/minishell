/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_structure.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbendu <sbendu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 16:19:22 by leldiss           #+#    #+#             */
/*   Updated: 2022/06/13 17:04:07 by sbendu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_arguments(t_arguments *arguments)
{
	t_arguments *tmp;

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
	t_execute *tmp;

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
		if (info->stdIn != NULL)
			free(info->stdIn);
		if (info->stdIn2 != NULL)
			free(info->stdIn2);
		if (info->stdOut != NULL)
			free(info->stdOut);
		if (info->stdOut2 != NULL)
			free(info->stdOut2);
		info = info->next;
		free(tmp);
	}
}

void free_all(t_execute *info)
{
	if (info != NULL)
		free_execute(info);
}

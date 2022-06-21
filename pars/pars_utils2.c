/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leldiss <leldiss@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 13:05:41 by leldiss           #+#    #+#             */
/*   Updated: 2022/06/21 18:28:33 by leldiss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*single_dollar(t_execute *info, char *line, int *i)
{
	info->argument->argument[*i] = '$';
	*i = *i + 1;
	line++;
	return (line);
}

char	*itoa(int number)
{
	char	*string;
	int		size;
	int		i;

	i = 0;
	size = status_size(number);
	string = malloc(size + 1);
	if (number == 0)
		string[i++] = '0';
	while (number > 0)
	{
		string[size - i - 1] = (number % 10) + '0';
		number = number / 10;
		i++;
	}
	string[i] = 0;
	return (string);
}

int	status_size(int number)
{
	int	i;

	i = 0;
	if (number == 0)
		return (1);
	while (number > 0)
	{
		number = number / 10;
		i++;
	}
	return (i);
}

char	*current_status(t_execute *info, char *line, int *i)
{
	char	*status;
	char	*tmp;

	status = itoa(info->info->status);
	tmp = status;
	while (*status)
	{
		info->argument->argument[*i] = *status;
		status++;
		*i = *i + 1;
	}
	free(tmp);
	line = line + 2;
	return (line);
}

char	*get_value(t_execute *info, char *key)
{
	t_list	*tmp;

	tmp = info->info->l_envp;
	while (tmp != NULL)
	{
		if (string_compare(key, tmp->key))
			return (tmp->value);
		tmp = tmp->next;
	}
	return (NULL);
}

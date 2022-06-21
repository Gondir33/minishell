/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_output.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leldiss <leldiss@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 14:00:28 by leldiss           #+#    #+#             */
/*   Updated: 2022/06/21 12:58:14 by leldiss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	if (str == NULL)
		return (0);
	while (str[i])
		i++;
	return (i);
}

char	*parse_double_output(t_execute *info, char *line)
{
	while ((*line >= 9 && *line <= 13) || *line == 32)
		line++;
	line = pure_argument(info, line);
	info->stdout = join_argument(info->argument->argument, NULL);
	info->argument->argument = NULL;
	return (line);
}

char	*parse_output(t_execute *info, char *line)
{
	if (*line == '>')
		line = parse_double_output(info, ++line);
	else
	{
		while ((*line >= 9 && *line <= 13) || *line == 32)
			line++;
		line = pure_argument(info, line);
		info->stdout = join_argument(info->argument->argument, NULL);
		info->argument->argument = NULL;
	}
	return (line);
}

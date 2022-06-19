/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_output.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leldiss <leldiss@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 14:00:28 by leldiss           #+#    #+#             */
/*   Updated: 2022/06/18 10:18:59 by leldiss          ###   ########.fr       */
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
	char	*str;
	int		i;

	while ((*line >= 9 && *line <= 13) || *line == 32)
		line++;
	i = 0;
	str = line;
	info->stdout2 = (char *)malloc(size_line(str) + 1);
	while (i < size_line(str))
	{
		info->stdout2[i] = *line;
		i++;
		line++;
	}
	info->stdout2[i] = 0;
	return (line);
}

char	*parse_output(t_execute *info, char *line)
{
	char	*str;
	int		i;

	if (*line == '>')
		line = parse_double_output(info, ++line);
	else
	{
		while ((*line >= 9 && *line <= 13) || *line == 32)
			line++;
		i = 0;
		str = line;
		info->stdout = (char *)malloc(size_line(str) + 1);
		while (i < size_line(str))
		{
			info->stdout[i] = *line;
			i++;
			line++;
		}
		info->stdout[i] = 0;
	}
	return (line);
}

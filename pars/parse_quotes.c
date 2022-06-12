/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbendu <sbendu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 16:24:52 by leldiss           #+#    #+#             */
/*   Updated: 2022/06/09 16:21:03 by sbendu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	size_line_quotes(char *str)
{
	int	i;

	i = 0;
	if (str == NULL)
		return 0;
	while (str[i] && str[i] != '\'')
		i++;
	return (i);
}

char	*parse_quotes(t_execute *info, char *line)
{
	char	*str;
	int	i;

	if (*line == '\'')
		return (++line);
	else
	{
		i = 0;
		str = line;
		if (info->argument->argument != NULL)
			new_argument(info);
		info->argument->argument = (char *)malloc(size_line_quotes(str) + 1);
		while (i < size_line_quotes(str))
		{
			info->argument->argument[i] = *line;
			i++;
			line++;
		}
		info->argument->argument[i] = 0;	
	}
	return (++line);
}

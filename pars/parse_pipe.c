/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leldiss <leldiss@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 17:43:02 by leldiss           #+#    #+#             */
/*   Updated: 2022/06/18 10:16:31 by leldiss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*next_command(t_execute *info, char *line)
{
	info = new_execute(info);
	first_argument(info);
	line = parse_command(info, line);
	while ((*line >= 9 && *line <= 13) || *line == 32)
		line++;
	if (*line == '-')
		line = parse_options(info, line);
	while (*line)
	{
		while ((*line >= 9 && *line <= 13) || *line == 32)
			line++;
		if ((*line <= 9 && *line >= 13) || (*line != 32 && *line))
			line = is_handle(info, line);
	}
	return (line);
}

char	*parse_pipe(t_execute *info, char	*line)
{
	while ((*line >= 9 && *line <= 13) || (*line == 32 && *line))
		line++;
	if (*line != '\0')
		line = next_command(info, line);
	return (line);
}

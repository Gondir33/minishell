/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbendu <sbendu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 17:43:02 by leldiss           #+#    #+#             */
/*   Updated: 2022/06/10 20:00:01 by sbendu           ###   ########.fr       */
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
			line = isHandle(info, line);
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
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbendu <sbendu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 13:49:22 by leldiss           #+#    #+#             */
/*   Updated: 2022/06/10 20:00:37 by sbendu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int size_line(char *line)
{
	int	i;

	i = 0;
	while (((line[i] <= 9 && line[i] >= 13) || line[i] != 32) && line[i])
	{
		i++;
	}
	return (i);
}

char *parse_options(t_execute *info, char *line)
{
	char *str;
	int	i;

	i = 0;
	str = line;
	info->option = (char *)malloc(size_line(str) + 1);
	while (i < size_line(str))
	{
		info->option[i] = *line;
		i++;
		line++;
	}
	info->option[i] = 0;
	return (line);
}

char *parse_command(t_execute *info, char *line)
{
	char *str;
	int	i;

	i = 0;
	str = line;
	info->command = (char *)malloc(size_line(str) + 1);
	while (i < size_line(str))
	{
		info->command[i] = *line;
		i++;
		line++;
	}
	info->command[i] = 0;
	return (line);
}

char	*isHandle(t_execute *info, char *line)
{
	if (*line == '>')
		line = parse_output(info, ++line);
	else if (*line == '<')
		line = parse_input(info, ++line);
	else if (*line == '\"')
			line = parse_double_quotes(info, ++line);
	else if (*line == '\'')
		line = parse_quotes(info, ++line);
	else if (*line == '$')
		line = parse_env(info, line);
	else if (*line == '|')
		line = parse_pipe(info, ++line);
	else if (((*line <= 9 && *line >= 13) || *line != 32) && *line)
		line = parse_arguments(info, line);
	return (line);
}

void	start_parse(t_execute *info, char *line)
{
	char *str;

	str = line;
	first_argument(info);
	while ((*line >= 9 && *line <= 13) || *line == 32)
		line++;
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
	free(str);
	info->argument = info->argument->head;
	info = info->head;
}
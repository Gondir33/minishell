/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leldiss <leldiss@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 13:49:22 by leldiss           #+#    #+#             */
/*   Updated: 2022/06/21 11:50:08 by leldiss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*parse_options(t_execute *info, char *line)
{
	char	*str;
	int		i;

	i = 0;
	str = line;
	info->option = (char *)malloc(size_command(str) + 1);
	while (i < size_command(str))
	{
		info->option[i] = *line;
		i++;
		line++;
	}
	info->option[i] = 0;
	return (line);
}

char	*pure_argument(t_execute *info, char *line)
{
	char	*tmp;

	tmp = NULL;
	if (info->argument->argument != NULL)
		new_argument(info);
	while (((*line <= 9 && *line >= 13)
			|| *line != 32) && *line != '\0')
	{
		if (*line == '\"')
			line = parse_double_quotes(info, ++line);
		else if (*line == '\'')
			line = parse_quotes(info, ++line);
		else if (*line == '$')
			line = parse_env(info, line);
		else if (((*line <= 9 && *line >= 13) || *line != 32) && *line)
			line = parse_arguments(info, line);
		tmp = join_argument(tmp, info->argument->argument);
	}
	info->argument->argument = tmp;
	return (line);
}

char	*parse_command(t_execute *info, char *line)
{
	line = pure_argument(info, line);
	if (info->argument->argument == NULL)
		return (line);
	if (string_compare(info->argument->argument, ""))
	{
		free(info->argument->argument);
		info->argument->argument = NULL;
		while ((*line >= 9 && *line <= 13) || *line == 32)
			line++;
		line = parse_command(info, line);
	}
	else
	{
		info->command = join_argument(info->argument->argument, NULL);
		info->argument->argument = NULL;
	}
	return (line);
}

char	*is_handle(t_execute *info, char *line)
{
	if (*line == '>')
		line = parse_output(info, ++line);
	else if (*line == '<')
		line = parse_input(info, ++line);
	else if (*line == '|')
		line = parse_pipe(info, ++line);
	else if (((*line <= 9 && *line >= 13) || *line != 32) && *line)
		line = pure_argument(info, line);
	return (line);
}

void	start_parse(t_execute *info, char *line)
{
	char	*str;

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
			line = is_handle(info, line);
	}
	free(str);
	info->argument = info->argument->head;
	info = info->head;
}

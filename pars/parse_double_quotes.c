/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_double_quotes.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbendu <sbendu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 17:02:33 by leldiss           #+#    #+#             */
/*   Updated: 2022/06/19 10:11:35 by sbendu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	final_size_dquotes(char	*line, t_execute *info)
{
	char	*key;
	int		i;

	i = 0;
	if ((line[1] == '?' && line[2] == '\0')
		|| (line[2] >= 9 && line[2] <= 13) || line[2] == 32)
		i = status_size(info->info->status);
	else
	{
		while ((*line <= 9 && *line >= 13) || (*line != 32
			&& *line && *line != '\"' && *line != '\''))
		{
			if (*line == '$')
			{
				if (((line[1] >= 9 && line[1] <= 13) || line[1] == 32)
					|| line[1] == '\0' || line[1] == '\"' || line[1] == '\'')
					i++;
				key = get_key(++line);
				i = i + ft_strlen(get_value(info, key));
				free(key);
			}
			line++;
		}
	}
	return (i);
}

int	size_line_dquotes(char *str, t_execute *info)
{
	int	i;

	i = 0;
	if (str == NULL)
		return (0);
	while (*str && *str != '\"')
	{
		if (*str == '$')
		{
			i = i + final_size_dquotes(str, info);
			while (((*str <= 9 && *str >= 13)
					|| *str != 32) && *str && *str != '\"' && *str != '\'')
				str++;
		}
		else
		{
			i++;
			str++;
		}
	}
	return (i);
}

char	*skip_lines(t_execute *info, char *line, int *i)
{
	if ((line[1] >= 9 && line[1] <= 13) || line[1] == 32
		|| line[1] == '\0' || line[1] == '\"' || line[1] == '\'')
		line = single_dollar(info, line, i);
	else if ((line[1] == '?' && line[2] == '\0')
		|| (line[2] >= 9 && line[2] <= 13)
		|| line[2] == 32 || line[2] == '\"' || line[2] == '\'')
		line = current_status(info, line, i);
	else
		line = get_env(info, line, i);
	return (line);
}

char	*parse_double_quotes2(t_execute	*info, char	*line, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		if (*line == '$')
			line = skip_lines(info, line, &i);
		else
		{
			info->argument->argument[i] = *line;
			i++;
			line++;
		}
	}
	info->argument->argument[i] = 0;
	return (line);
}

char	*parse_double_quotes(t_execute *info, char *line)
{
	int	size;

	if (*line == '\"')
		return (++line);
	else
	{
		size = size_line_dquotes(line, info);
		if (size != 0)
		{
			info->argument->argument = malloc(size + 1);
			line = parse_double_quotes2(info, line, size);
		}
		else
		{
			while (*line && *line != '\"')
				line++;
			info->argument->argument = NULL;
		}
	}
	return (++line);
}

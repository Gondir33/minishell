/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leldiss <leldiss@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 13:58:42 by leldiss           #+#    #+#             */
/*   Updated: 2022/06/21 11:10:46 by leldiss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*parse_arguments(t_execute *info, char *line)
{
	char	*str;
	int		i;

	i = 0;
	str = line;
	info->argument->argument = (char *)malloc(size_line(str) + 1);
	while (i < size_line(str))
	{
		info->argument->argument[i] = *line;
		i++;
		line++;
	}
	info->argument->argument[i] = 0;
	return (line);
}

char	*get_env(t_execute *info, char *line, int *i)
{
	char	*value;
	char	*key;

	key = get_key(++line);
	value = get_value(info, key);
	if (value)
	{
		while (*value)
		{
			info->argument->argument[*i] = *value;
			value++;
			*i = *i + 1;
		}
	}
	if (line[0] == '$')
		line = line + 1;
	else
	{
		while (((*line <= 9 && *line >= 13) || *line != 32)
			&& *line != '\0' && *line != '$' && *line != '\'' && *line != '\"')
			line++;
	}
	free(key);
	return (line);
}

char	*parse_env2(t_execute *info, char *line, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		if ((line[1] >= 9 && line[1] <= 13)
			|| line[1] == 32 || line[1] == '\0')
			line = single_dollar(info, line, &i);
		else if (line[1] == '?' && (line[2] == '\0'
				|| (line[2] >= 9 && line[2] <= 13) || line[2] == 32))
			line = current_status(info, line, &i);
		else
			line = get_env(info, line, &i);
	}
	info->argument->argument[i] = 0;
	return (line);
}

int	final_size_env(char	*line, t_execute *info)
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
				&& *line && *line != '\'' && *line != '\"'))
		{
			if (*line == '$')
			{
				if ((line[1] >= 9 && line[1] <= 13)
					|| line[1] == 32 || line[1] == '\0')
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

char	*parse_env(t_execute *info, char *line)
{
	int	size;

	size = final_size_env(line, info);
	if (size != 0)
	{
		info->argument->argument = malloc(size + 1);
		line = parse_env2(info, line, size);
	}
	else
	{
		if (line[0] == '$' && line[1] == '$')
			line = line + 2;
		else
		{
			while (*line && ((*line <= 9 && *line >= 13)
					|| *line != 32) && *line != '\'' && *line != '\"')
				line++;
		}
		info->argument->argument = NULL;
	}
	return (line);
}

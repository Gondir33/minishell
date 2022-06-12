/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_double_quotes.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leldiss <leldiss@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 17:02:33 by leldiss           #+#    #+#             */
/*   Updated: 2022/06/07 21:10:26 by leldiss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int size_line_env(char *line)
{
	int	i;

	i = 0;
	while (((line[i] <= 9 && line[i] >= 13) 
		|| line[i] != 32) && line[i] && line[i] != '\"' && line[i] != '$')
	{
		i++;
	}
	return (i);
}

int	size_line_dquotes(char *str)
{
	int	i;

	i = 0;
	if (str == NULL)
		return 0;
	while (*str && *str != '\"')
	{
		if (*str == '$')
		{
			while (((*str <= 9 && *str >= 13) 
				|| *str != 32) && *str && *str != '\"')
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

char *skip_lines(t_execute *info, char *line, int *i)
{
	while (*line && *line != '\"')
	{
		if (line[1] == '$' || line[1] == '\0' || line[1] == '\"' ||
			(line[1] >= 9 && line[1] <= 13) || line[1] == 32)
		{
			*i = single_dollar(info, line, *i);
			line++;
		}
		else
		{
			*i = parse_env2(info, line, *i);
			line++;
			while (((*line <= 9 && *line >= 13) 
				|| *line != 32) && *line && *line != '\"' && *line != '$')
			line++;
		}
	}
	return (line);
}

char	*parse_double_quotes2(t_execute	*info, char	*line, int size)
{
	int	i;

	i = 0;
	printf("line is %c\n", *line);
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
	int size;

	if (*line == '\"')
		return (++line);
	else
	{
		size = final_size_dquotes(line) + size_line_dquotes(line);
		if (size != 0)
		{
			if (info->argument->argument != NULL)
				new_argument(info);
			info->argument->argument = malloc(size + 1);
			line = parse_double_quotes2(info, line, size);
		}
		else
		{
			while (*line && *line != '\"')
				line++;
		}
	}
	return (++line);	
}
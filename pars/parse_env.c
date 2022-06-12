/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbendu <sbendu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 13:58:42 by leldiss           #+#    #+#             */
/*   Updated: 2022/06/10 19:59:44 by sbendu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	final_size_dquotes(char	*line)
{
	char	*get;
	int	i;

	i = 0;
	while ( *line && *line != '\"')
	{
		if (*line == '$')
		{
			if (line[1] == '$' || line[1] == '\0' || line[1] == '\"' ||
			(line[1] >= 9 && line[1] <= 13) || line[1] == 32)
				i++;
			else
			{
				get = get_env(line);
				line++;
				i = i + ft_strlen(getenv(get));
				free(get);
			}
		}
		line++;
	}
	return (i);
}

int	final_size_env(char	*line)
{
	char	*get;
	int	i;

	i = 0;
	while ((*line <= 9 && *line >= 13)
		|| (*line != 32 && *line))
	{
		if (*line == '$')
		{
			if (line[1] == '$' || line[1] == '\0' || line[1] == '\"' ||
			(line[1] >= 9 && line[1] <= 13) || line[1] == 32)
				i++;
			else
			{
				get = get_env(line);
				line++;
				i = i + ft_strlen(getenv(get));
				free(get);
			}
		}
		line++;
	}
	return (i);
}

char	*get_env(char	*str)
{
	char	*get_env;
	int	i;

	get_env = NULL;
	i = 0;
	if (*str++ == '$')
	{
		get_env = (char *)malloc(size_line_env(str) + 1);
	while (((*str <= 9 && *str >= 13) 
		|| *str != 32) && *str && *str != '\"' && *str != '$')
		{
			get_env[i] = *str;
			i++;
			str++;
		}
		get_env[i] = 0;
	}
	return (get_env);
}

char	*parse_arguments(t_execute *info, char *line)
{
	char *str;
	int	i;

	i = 0;
	str = line;
	if (info->argument->argument != NULL)
		new_argument(info);
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

char	*parse_env3(t_execute *info, char *line, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		if (*line == '$')
		{
			if (line[1] == '$' || line[1] == '\0' || 
				(line[1] >= 9 && line[1] <= 13) || line[1] == 32)
				{
					i = single_dollar(info, line, i);
					line++;
				}
			else
			{
				i = parse_env2(info, line, i);
				while (*line && ((*line <= 9 && *line >= 13) 
					|| *line != 32))
					line++;
			}
		}
	}
	info->argument->argument[i] = 0;
	return (line);	
}

int	parse_env2(t_execute *info, char *line, int i)
{
	char	*get;
	char	*env;

	get = get_env(line);
	env = getenv(get);
	if (env)
	{
		while (*env)
		{
			info->argument->argument[i] = *env;
			env++;
			i++;
		}
	}
	free(get);
	return (i);
}

char *parse_env(t_execute *info, char *line)
{
	int	size;
	
	size = final_size_env(line);
	printf("size is %d\n", size);
	if (size != 0)
	{
		if (info->argument->argument != NULL)
			new_argument(info);
		info->argument->argument = malloc(size + 1);
			line = parse_env3(info, line, size);
	}
	else
	{
		while (*line && ((*line <= 9 && *line >= 13) 
			|| *line != 32))
			line++;
	}
	return (line);
}

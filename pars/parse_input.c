/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leldiss <leldiss@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 16:49:47 by leldiss           #+#    #+#             */
/*   Updated: 2022/06/21 13:04:02 by leldiss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strjoin(char *first, char *second)
{
	int		i;
	char	*tmp;

	i = 0;
	tmp = (char *)malloc(ft_strlen(first) + ft_strlen(second) + 2);
	while (first[i])
	{
		tmp[i] = first[i];
		i++;
	}
	tmp[i] = '\n';
	i++;
	while (*second)
	{
		tmp[i] = *second;
		i++;
		second++;
	}
	tmp[i] = 0;
	free(first);
	return (tmp);
}

char	*dup_n(char	*final)
{
	char	*dup;
	int		i;

	i = 0;
	dup = malloc(ft_strlen(final) + 2);
	while (final[i])
	{
		dup[i] = final[i];
		i++;
	}
	dup[i] = '\n';
	dup[i + 1] = 0;
	free(final);
	return (dup);
}

char	*parse_double_input2(char *docstr)
{
	char	*line;
	char	*final_str;

	final_str = readline ("heredoc> ");
	if (string_compare(final_str, docstr))
	{
		free(final_str);
		return (NULL);
	}
	while (1)
	{
		line = readline("heredoc> ");
		if (string_compare(line, docstr))
			break ;
		final_str = ft_strjoin(final_str, line);
		free(line);
	}
	free(line);
	return (dup_n(final_str));
}

char	*parse_double_input(t_execute *info, char *line)
{
	char	*str;
	char	*docstr;
	int		i;

	while ((*line >= 9 && *line <= 13) || *line == 32)
		line++;
	i = 0;
	str = line;
	docstr = (char *)malloc(size_line(str) + 1);
	while (i < size_line(str))
	{
		docstr[i] = *line;
		i++;
		line++;
	}
	docstr[i] = 0;
	info->stdin2 = parse_double_input2(docstr);
	free(docstr);
	return (line);
}

char	*parse_input(t_execute *info, char *line)
{
	if (*line == '<')
		line = parse_double_input(info, ++line);
	else
	{
		while ((*line >= 9 && *line <= 13) || *line == 32)
			line++;
		line = pure_argument(info, line);
		info->stdin = join_argument(info->argument->argument, NULL);
		info->argument->argument = NULL;
	}
	return (line);
}

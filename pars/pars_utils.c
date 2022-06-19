/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leldiss <leldiss@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 13:03:12 by leldiss           #+#    #+#             */
/*   Updated: 2022/06/18 13:05:34 by leldiss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	string_compare(char *str1, char *str2)
{
	int	i;

	i = 0;
	while (str1[i] || str2[i])
	{
		if (str1[i] != str2[i])
			return (0);
		i++;
	}
	return (1);
}

int	size_line_env(char *line)
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

int	size_line(char *line)
{
	int	i;

	i = 0;
	while (((line[i] <= 9 && line[i] >= 13) || line[i] != 32)
		&& line[i] && line[i] != '$' && line[i] != '\'' && line[i] != '\"')
	{
		i++;
	}
	return (i);
}

char	*join_argument2(char *tmp, char *str2, int *index)
{
	int	i;

	i = 0;
	while (str2[i] != '\0')
	{
		tmp[*index] = str2[i];
		i++;
		*index = *index + 1;
	}
	return (tmp);
}

char	*join_argument(char *str1, char *str2)
{
	int		i;
	char	*tmp;

	i = 0;
	tmp = malloc(ft_strlen(str1) + ft_strlen(str2) + 1);
	if (str1 != NULL)
	{
		while (str1[i] != '\0')
		{
			tmp[i] = str1[i];
			i++;
		}
		free(str1);
	}
	if (str2 != NULL)
	{
		tmp = join_argument2(tmp, str2, &i);
		free(str2);
	}
	tmp[i] = 0;
	return (tmp);
}

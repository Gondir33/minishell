/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_utils3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leldiss <leldiss@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 13:16:51 by leldiss           #+#    #+#             */
/*   Updated: 2022/06/21 10:44:21 by leldiss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*first_lenvp(void)
{
	t_list	*tmp;

	tmp = malloc(sizeof(*tmp));
	tmp->key = NULL;
	tmp->value = NULL;
	tmp->head = tmp;
	tmp->next = NULL;
	return (tmp);
}

void	next_lenvp(t_info *info)
{
	t_list	*tmp;

	tmp = malloc(sizeof(*tmp));
	tmp->key = NULL;
	tmp->value = NULL;
	tmp->head = info->l_envp->head;
	tmp->next = NULL;
	info->l_envp->next = tmp;
	info->l_envp = tmp;
}

char	*get_key(char	*str)
{
	char	*key;
	int		i;

	key = NULL;
	i = 0;
	if (*str == '$')
	{
		key = (char *)malloc(2);
		key[0] = '$';
		key[1] = 0;
	}
	else
	{
		key = (char *)malloc(size_line_env(str) + 1);
		while (((*str <= 9 && *str >= 13) || *str != 32)
			&& *str && *str != '\"' && *str != '$' && *str != '\'')
		{
			key[i] = *str;
			i++;
			str++;
		}
		key[i] = 0;
	}
	return (key);
}

int	size_command(char *line)
{
	int	i;

	i = 0;
	while (((line[i] <= 9 && line[i] >= 13) || line[i] != 32)
		&& line[i])
	{
		i++;
	}
	return (i);
}

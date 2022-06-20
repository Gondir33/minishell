/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtinsutils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbendu <sbendu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 13:08:33 by sbendu            #+#    #+#             */
/*   Updated: 2022/06/20 14:40:15 by sbendu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

char	*ft_strrcut(char *arg, char c)
{
	int		len;
	char	*s;
	int		i;
	int		j;

	j = -1;
	len = ft_strlen(arg);
	i = len;
	while (arg[--i] != c)
		;
	s = malloc(len - i);
	if (s == NULL)
		return (NULL);
	s[len - i - 1] = 0;
	while (arg[++i])
		s[++j] = arg[i];
	return (s);
}
char	*ft_strcut(char *arg, char c)
{
	int		len;
	char	*s;
	int		i;
	
	len = -1;
	while (arg[++len] != c)
		;
	s = malloc(len + 1);
	s[len] = 0;
	i = -1;
	while (++i < len)
		s[i] = arg[i];
	return (s);
}

int	check_key(t_list *lst, char *key, char *value)
{
	lst = lst->head;
	while (lst)
	{
		if (ft_strncmp(lst->key, key, ft_strlen(key)) == 0)
		{
			free(lst->value);
			free(lst->key);
			lst->value = value;
			lst->key = key;
			return (0);
		}
		lst = lst->next;
	}
	return (-1);
}

int add_envp(t_list *lst, char *key, char *value)
{
	lst = lst->head;
	while (lst->next)
		lst = lst->next;
	lst->next = malloc(sizeof(t_list));
	if (lst->next == 0)
		return (-1);
	lst->next->head = lst->head;
	lst->next->next = NULL;
	lst->next->key = key;
	lst->next->value = value;
	return (0);
}

int ft_arg_len(char **arg)
{
	int	i;

	i = 0;
	while (arg[i])
		i++;
	return (i);
}
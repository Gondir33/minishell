/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leldiss <leldiss@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 09:58:47 by leldiss           #+#    #+#             */
/*   Updated: 2022/06/21 17:12:41 by leldiss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "../execute/execute.h"

char	*join_prompt(char *str1, char *str2, int k)
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
	}
	if (str2 != NULL)
	{
		tmp = join_argument2(tmp, str2, &i);
	}
	tmp[i] = 0;
	if (k == 5)
		free(str1);
	return (tmp);
}

char	*printdir(void)
{
	char	cwd[1024];
	char	*username;
	char	*tmp;

	username = getenv("USER");
	getcwd(cwd, sizeof(cwd));
	tmp = join_prompt("\001\033[1;91m\002", username, 0);
	tmp = join_prompt(tmp, " \001\033[1;94m\002in \001\033[1;95m\002", 5);
	tmp = join_prompt(tmp, cwd, 5);
	tmp = join_prompt(tmp, " \001\033[1;97m\002> ", 5);
	return (tmp);
}

char	*ft_readline(void)
{
	char	*s;
	char	*prompt;

	prompt = printdir();
	s = readline(prompt);
	free(prompt);
	prompt = NULL;
	if (s)
		add_history(s);
	return (s);
}

int	main(int ac, char **av, char *envp[])
{
	t_execute	*info;
	t_info		information;
	char		*line;

	(void)ac;
	(void)av;
	init_info(&information, envp);
	get_envp(&information, envp);
	while (1)
	{
		make_signals_work(&information);
		info = first_execute();
		info->info = &information;
		line = ft_readline();
		if (line == NULL)
			ft_exit(info, &information);
		start_parse(info, line);
		if (info->command != NULL)
			execute(info, &information);
		free_all(info);
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leldiss <leldiss@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 09:58:47 by leldiss           #+#    #+#             */
/*   Updated: 2022/06/21 11:40:36 by leldiss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "../execute/execute.h"

void printDir(void)
{
	char	cwd[1024];
	char *username;

	username = getenv("USER");
	getcwd(cwd, sizeof(cwd));
	printf("\001\033[1;91m\002%s \001\033[1;94m\002in \001\033[1;95m\002%s ", username, cwd);
}

char	*ft_readline(char *p)
{
	char	*s;

	s = readline(p);
	if (s)
		add_history(s);
	return (s);
}

int main(int ac, char **av, char *envp[])
{
	t_execute	*info;
	t_info		information;
	(void)ac;
	(void)av;
	char *line;

	init_info(&information, envp);
	get_envp(&information, envp);
	while(1)
	{
		make_signals_work();
		info = first_execute();
		printDir();
		info->info = &information;
		line = ft_readline("\001\033[1;97m\002> ");
		if (line == NULL)
			ft_exit(info, &information);
		start_parse(info, line);
		if (info->command != NULL)
			execute(info, &information);
		free_all(info);
	}
	exit(0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbendu <sbendu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 09:58:47 by leldiss           #+#    #+#             */
/*   Updated: 2022/06/13 17:28:00 by sbendu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "../execute/execute.h"

void printDir()
{
	char	cwd[1024];
	char *username;

	username = getenv("USER");
	getcwd(cwd, sizeof(cwd));
	printf("%s in %s ", username, cwd);
}

void	init_info(t_info *info, char **envp)
{
	info->envp = envp;
	info->status = 0;
	info->l_envp = NULL;
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

	info = first_execute();
	printDir();
	line = ft_readline("> ");
	start_parse(info, line);
	init_info(&information, envp);
	// while (info != NULL)
	// {
	// 	printf("Command is %s\n", info->command);
	// 	printf("Option is %s\n", info->option);
	// 	printf("Output is %s\n", info->stdOut);
	// 	printf("Output2 is %s\n", info->stdOut2);
	// 	printf("Input is %s\n", info->stdIn);
	// 	printf("Input2 is %s\n", info->stdIn2);
	// 	info->argument = info->argument->head;
	// 	int i = 1;
	// 	t_arguments *kek = info->argument;
	// 	while (kek != NULL)
	// 	{
	// 		printf("argument %d = %s end\n", i, kek->argument);
	// 		i++;
	// 		kek = kek->next;
	// 	}
	// 	info = info->next;		
	// }
	execute(info, &information);
	free_all(info);
	exit(0);
}
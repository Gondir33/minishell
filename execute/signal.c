/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbendu <sbendu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 11:26:10 by sbendu            #+#    #+#             */
/*   Updated: 2022/06/21 12:55:17 by sbendu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

void	display_prompt(void)
{	
	write(1, "\n", 1);
	printDir();
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void	make_signals_work(void)
{
	signal(SIGINT, sighandler);
	signal(SIGQUIT, SIG_IGN);
	handle_ctrl_c(5000, NULL);
	handle_ctrl_qu(5000, NULL);
}

void	sighandler(int signal)
{
	if (signal == SIGINT)
		handle_ctrl_c(signal, NULL);
	if (signal == SIGQUIT)
		handle_ctrl_qu(signal, NULL);
}

void	handle_ctrl_c(int signal, int *ptr)
{
	static pid_t	*saved = NULL;
	int				i;

	i = -1;
	if (signal == 5000)
		saved = ptr;
	if (signal == SIGINT)
	{
		if (saved == NULL)
			display_prompt();
		else
		{
			while (saved[++i])
				kill(saved[i], SIGTERM);
			printf("\n");
			saved = NULL;
			saved = saved;
		}
	}
}

void	handle_ctrl_qu(int signal, int *ptr)
{
	static int	*saved = NULL;
	int			i;

	i = 0;
	if (signal == 5000)
		saved = ptr;
	if (signal == SIGQUIT)
	{
		if (saved != NULL)
		{
			printf("Quit\n");
			while (saved[i])
			{
				kill(saved[i], SIGTERM);
				i++;
			}
			saved = NULL;
			saved = saved;
		}
	}
}

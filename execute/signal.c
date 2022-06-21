/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbendu <sbendu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 11:26:10 by sbendu            #+#    #+#             */
/*   Updated: 2022/06/21 10:54:03 by sbendu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

void	display_prompt(void)
{	
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
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
	static int	*saved = NULL;
	int			i;

	if (signal == 5000)
		saved = ptr;
	if (signal == SIGINT)
	{
		if (saved == NULL)
		{
			printf("\n");
			printDir();
		}
		else
		{
			i = -1;
			while (saved[++i] != 0)
			{
				printf("pid is %d\n", saved[i]);
				kill(saved[i], SIGTERM);
			}
			// printf("\n");
		}
	}
}

void	handle_ctrl_qu(int signal, int *ptr)
{
	static int	*saved = NULL;
	int			i;

	if (signal == 5000)
		saved = ptr;
	if (signal == SIGINT)
	{
		if (saved == NULL)
		{
			
		}
		else
		{
			i = -1;
			while (saved[++i] != 0)
				kill(saved[i], SIGTERM);
			printf("Quit\n");
			printDir();
		}
	}
}

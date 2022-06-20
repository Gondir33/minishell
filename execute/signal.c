/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbendu <sbendu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 11:26:10 by sbendu            #+#    #+#             */
/*   Updated: 2022/06/20 23:20:01 by sbendu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

void	sighandler(int signal)
{
	if (signal == SIGINT)
	{
		handle_ctrl_c(signal, NULL);
	}
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
			rl_on_new_line();
			rl_replace_line("", 1);
			rl_redisplay();
		}
		else
		{
			i = -1;
			while (saved[++i] != 0)
				kill(saved[i], SIGTERM);
		}
	}
}

// int	handle_ctrl_d(const int signal, int *ptr)
// {
// 	static int	*saved = NULL;
// 	int			i;
// 	if (signal == 5000)
// 		saved = ptr;
// 	if (signal == EOF)
// 	{
// 		if (saved == NULL)
// 			;
// 	}
// }

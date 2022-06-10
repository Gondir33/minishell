# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "libft/libft.h"

static void	the_end(int sig, siginfo_t *info, void *context)
{
	pid_t	pid;

	pid = (pid_t *)context;
	kill(pid, SIGKILL);
}

int main()
{
	struct sigaction	act;
	pid_t				pid;
	int					i;

	act.sa_sigaction = the_end;
	sigemptyset(&act.sa_mask);
	pid = fork();
	sigaction(SIGINT, &act, pid);
	if (!pid)
	{
		while(1)
			printf("yes\n");
	}
}
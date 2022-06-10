# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
/*
int main(int ac, char **av, char *envp[])
{
	int		i;
	int		pipe_fd[2];
	int		status;
	char	*cmds[3][2] = {{"/usr/bin/yes", NULL},{"/usr/bin/head", NULL}, {"/usr/bin/wc", NULL}};
	i = -1;

	while (++i < 3)
	{
		pipe(pipe_fd);
		if (!fork())
		{
			dup2(pipe_fd[1],1);
			close(pipe_fd[0]);
			
			status = execve(cmds[i][0], cmds[i], envp);
			close(pipe_fd[1]);
			exit(status);
		}
		dup2(pipe_fd[0], 0);
		close(pipe_fd[1]);
		wait(&status);
		close(pipe_fd[0]);
	}
}*/


int main(int ac, char **av, char *envp[])
{
	int i;
	int	fd;
	char	*s;

	fd = open("sss", O_WRONLY | O_TRUNC | O_CREAT);
	write(fd, "12dsadsadsa3", 10);
}
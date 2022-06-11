# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>

int main(int ac, char **av, char *envp[])
{
	int		i;
	int		pipe_fd[2][2];
	pid_t	pid[3];
	int		status;
	char	*cmds[3][2] = {{"/usr/bin/yes", NULL},{"/usr/bin/hea", NULL}, {"/usr/bin/wc", NULL}};
	i = -1;

	pipe(pipe_fd[0]);
	pid[2] = fork();
	if (!pid[2])
	{
		dup2(pipe_fd[0][0], 0);
		close(pipe_fd[0][0]);
		close(pipe_fd[0][1]);
		execve(cmds[2][0], cmds[2], envp);
		exit(0);
	}
	close(pipe_fd[0][0]);
	pipe(pipe_fd[1]);
	pid[1] = fork();
	if (!pid[1])
	{
		dup2(pipe_fd[1][0], 0);
		close(pipe_fd[1][0]);
		close(pipe_fd[1][1]);
		dup2(pipe_fd[0][1], 1);
		close(pipe_fd[0][1]);
		close(pipe_fd[0][0]);
		execve(cmds[1][0], cmds[1], envp);
		exit(-1);
	}
	close(pipe_fd[0][1]);
	close(pipe_fd[1][0]);
	pid[0] = fork();
	if (!pid[0])
	{
		dup2(pipe_fd[1][1], 1);
		close(pipe_fd[1][1]);
		close(pipe_fd[1][0]);
		execve(cmds[0][0], cmds[0], envp);
		exit(0);
	}
	close(pipe_fd[1][1]);
	waitpid(pid[0], &status, 0);
	waitpid(pid[1], &status, 0);
	waitpid(pid[2], &status, 0);
}


// int main(int ac, char **av, char *envp[])
// {
// 	int i;
// 	int	fd;
// 	char	*s;

// 	fd = open("sss", O_WRONLY | O_TRUNC | O_CREAT);
// 	write(fd, "12dsadsadsa3", 10);
// }
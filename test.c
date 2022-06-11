# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>

int	main()
{
	int	fd;
	char	*s="sad";
	fd = open(s, O_RDONLY);
}
# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <signal.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	if (str == NULL)
		return 0;
	while (str[i])
		i++;
	return (i);
}

int size_line_env(char *line)
{
	int	i;

	i = 0;
	while (((line[i] <= 9 && line[i] >= 13) 
		|| line[i] != 32) && line[i] && line[i] != '\"' && line[i] != '$')
	{
		i++;
	}
	return (i);
}

char	*get_env(char	*str)
{
	char	*get_env;
	int	i;

	get_env = NULL;
	i = 0;
	while (((*str <= 9 && *str >= 13) 
		|| *str != 32) && *str && *str != '\"' && *str != '$')
	{
		str++;
	}
	if (*str++ == '$')
	{
		get_env = (char *)malloc(size_line_env(str) + 1);
	while (((*str <= 9 && *str >= 13) 
		|| *str != 32) && *str && *str != '\"' && *str != '$')
		{
			get_env[i] = *str;
			i++;
			str++;
		}
		get_env[i] = 0;
	}
	return (get_env);
}

int	size_line_dquotes(char *str)
{
	int	i;

	i = 0;
	if (str == NULL)
		return 0;
	while (*str && *str != '\"')
	{
		if (*str == '$')
		{
			while (((*str <= 9 && *str >= 13) 
				|| *str != 32) && *str && *str != '\"')
				str++;
		}
		else
		{
			i++;
			str++;
		}
	}
	return (i);
}

int	size_final_quotes(char	*line)
{
	char	*get;
	char	*env;
	int	i;

	i = 0;
	while (*line)
	{
		if (*line == '$')
		{
			get = get_env(line);
			while (((*line <= 9 && *line >= 13) 
				|| *line != 32) && *line && *line != '\"' && *line != '$')
			line++;
			printf("get do h%sh\n", get);
			printf("do %d\n", i);
			printf("schet %d\n", ft_strlen(getenv(get)));
			i = i + ft_strlen(getenv(get));
			printf("posle %d\n", i);
			free(get);
			env = NULL;
		}
		line++;
	}
	return (i);
}

int main()
{
	printf("%s\n", getenv("$"));
}

// void	parse_env2(t_execute *info, char *get_env)
// {
// 	int	i;
// 	int	size;
// 	char *env;
	
// 	i = 0;
// 	env = getenv(get_env);
// 	if (env)
// 	{
// 		size = ft_strlen(env);
// 		if (info->argument->argument != NULL)
// 			new_argument(info);
// 		info->argument->argument = (char *)malloc(size + 10);
// 		while (i <= size)
// 		{
// 			info->argument->argument[i] = *env;
// 			i++;
// 			env++;
// 		}
// 		info->argument->argument[i] = 0;
// 	}
// }

// char *parse_env(t_execute *info, char *line)
// {
// 	char *str;
// 	char *get_env;
// 	int	i;

// 	i = 0;
// 	str = line;
// 	get_env = (char *)malloc(size_line(str) + 1);
// 	while (i < size_line(str))
// 	{
// 		get_env[i] = *line;
// 		i++;
// 		line++;
// 	}
// 	get_env[i] = 0;
// 	parse_env2(info, get_env);
// 	free(get_env);
// 	return (line);
// }



// void	parse_env2(t_execute *info, char *get_env)
// {
// 	int	i;
// 	int	size;
// 	char *env;
	
// 	i = 0;
// 	env = getenv(get_env);
// 	if (env)
// 	{
// 		size = ft_strlen(env);
// 		if (info->argument->argument != NULL)
// 			new_argument(info);
// 		info->argument->argument = (char *)malloc(size + 10);
// 		while (i <= size)
// 		{
// 			info->argument->argument[i] = *env;
// 			i++;
// 			env++;
// 		}
// 		info->argument->argument[i] = 0;
// 	}
// }

// char *parse_env(t_execute *info, char *line)
// {
// 	char *str;
// 	char *get_env;
// 	int	i;

// 	i = 0;
// 	str = line;
// 	get_env = (char *)malloc(size_line_env(str) + 1);
// 	while (i < size_line_env(str))		
// 	{
// 		get_env[i] = *line;
// 		i++;
// 		line++;
// 	}
// 	get_env[i] = 0;
// 	parse_env2(info, get_env);
// 	free(get_env);
// 	return (line);
// }
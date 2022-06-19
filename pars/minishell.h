/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbendu <sbendu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 13:50:14 by leldiss           #+#    #+#             */
/*   Updated: 2022/06/19 12:01:28 by sbendu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <signal.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>
# define NUM_BUILTNS 7

// Структура для аргументов, чтобы не релоцировать память
typedef struct s_arguments
{
	char				*argument;
	struct s_arguments	*next;
	struct s_arguments	*head;
}	t_arguments;

typedef struct s_list
{
	char			*key;
	char			*value;
	struct s_list	*head;
	struct s_list	*next;
}t_list;

typedef struct s_info
{
	char			**envp;
	t_list			*l_envp;
	int				status;
	int				*pid_child;
}t_info;

// Общая структура для выполнения команд оболочкой
typedef struct s_execute
{
	char				*command;
	char				*option;
	t_arguments			*argument;
	char				**arguments;
	char				*stdin;
	char				*stdin2;
	char				*stdout;
	char				*stdout2;
	t_info				*info;
	struct s_execute	*next;
	struct s_execute	*head;
}	t_execute;

typedef struct s_pipex
{
	int		num_pipes;
	int		*pipe_fd;
	int		*pid;
	int		temp_0_fd;
	int		temp_1_fd;
	t_info	*info;
}	t_pipex;

// Инициализация и заполнения переменных окружения
void		init_info(t_info *info, char **envp);
t_list		*first_lenvp(void);
void		next_lenvp(t_info *info);
void		malloc_envp(t_info *info, char *envp);
int			fill_key(t_info *info, char *envp);
void		fill_value(t_info *info, char *envp, int index);
void		get_envp(t_info *info, char **envp);

// Инициализия структур и их очистка
t_execute	*first_execute(void);
t_execute	*new_execute(t_execute *info);
void		first_argument(t_execute *info);
void		new_argument(t_execute *info);
void		free_arguments(t_arguments *arguments);
void		free_execute(t_execute *info);
void		free_all(t_execute *info);

// Функции парсера и лексера
int			ft_strlen(char *str);
int			size_line(char *line);
// int			final_size_env(char	*line);

// Парсинг > и >>
char		*parse_double_output(t_execute *info, char *line);
char		*parse_output(t_execute *info, char *line);

// Парсинг < и <<
char		*ft_strjoin(char *first, char *second);
int			string_compare(char *str1, char *str2);
char		*dup_n(char	*final);
char		*parse_double_input2(char *docstr);
char		*parse_double_input(t_execute *info, char *line);
char		*parse_input(t_execute *info, char *line);

// Парсинг ""
int			size_line_env(char *line);
// char	*get_env(char	*str);
int			final_size_dquotes(char	*line, t_execute *info);
int			size_line_dquotes(char *str, t_execute *info);
char		*parse_double_quotes2(t_execute	*info, char	*line, int size);
char		*parse_double_quotes(t_execute *info, char *line);

// Парсинг ''
int			size_line_quotes(char *str);
char		*parse_quotes(t_execute *info, char *line);

// Парсинг |
char		*next_command(t_execute *info, char *line);
char		*parse_pipe(t_execute *info, char	*line);

// Парсинг переменных окружения и аргументов
char		*parse_arguments(t_execute *info, char *line);
char		*single_dollar(t_execute *info, char *line, int *i);
char		*get_key(char	*str);
char		*current_status(t_execute *info, char *line, int *i);
char		*get_value(t_execute *info, char *key);
char		*get_env(t_execute *info, char *line, int *i);
char		*parse_env2(t_execute *info, char *line, int size);
int			final_size_env(char	*line, t_execute *info);
char		*parse_env(t_execute *info, char *line);
int			status_size(int number);
char		*itoa(int number);

// Парсинг команды и флагов
char		*parse_options(t_execute *info, char *line);
char		*parse_command(t_execute *info, char *line);

// Начало парсинга
char		*is_handle(t_execute *info, char *line);
char		*join_argument2(char *tmp, char *str2, int *index);
char		*join_argument(char *str1, char *str2);
void		start_parse(t_execute *info, char *line);

// Мемная функция
void		printDir(void);

#endif
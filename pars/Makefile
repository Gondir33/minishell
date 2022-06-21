NAME = minishell

CC = gcc

CFLAGS = -lreadline -g -Wall -Werror -Wextra

INCLD = pars/minishell.h execute/execute.h

SRC = ./pars/main.c\
		./pars/free_structure.c\
		./pars/initialize_structure.c\
		./pars/parse_double_quotes.c\
		./pars/parse_env.c\
		./pars/parse_input.c\
		./pars/parse_output.c\
		./pars/parse_pipe.c\
		./pars/parse_quotes.c\
		./pars/start_parse.c\
		./pars/env_utils.c\
		./pars/pars_utils.c\
		./pars/pars_utils2.c\
		./pars/pars_utils3.c\
		./execute/execute.c\
		./execute/pipex.c\
		./execute/utils.c\
		./execute/utils2.c\
		./execute/pwd.c\
		./execute/builtinsutils.c\
		./execute/cd.c\
		./execute/echo.c\
		./execute/env.c\
		./execute/exit.c\
		./execute/export.c\
		./execute/unset.c\
		./execute/signal.c\
		./execute/path.c\
		./execute/utils3.c\
		./execute/ft_split.c\

OBJ = $(SRC:.c=.o)

all:	$(NAME)

$(NAME): $(OBJ) $(INCLD)
	$(CC) $^ -o $@ $(CFLAGS) -o $(NAME)

%.o: %.c  $(INCLD) $(SRC)
	$(CC) $(CFLAGS) -c $< -o $(<:.c=.o)

clean:
	rm -rf $(OBJ) 

fclean: clean
	rm -rf $(NAME)

re: fclean  all

.PHONY : all clean fclean re
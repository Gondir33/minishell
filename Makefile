NAME = minishell

CC = gcc

CFLAGS = -lreadline -g

INCLD =./execute/\

SRC = ./parser/main.c\
		./parser/free_structure.c\
		./parser/initialize_structure.c\
		./parser/parse_double_quotes.c\
		./parser/parse_env.c\
		./parser/parse_input.c\
		./parser/parse_output.c\
		./parser/parse_pipe.c\
		./parser/parse_quotes.c\
		./parser/start_parse.c\
		./execute/execute.c\
		./execute/pipex.c\
		./execute/utils.c\


OBJ = $(SRC:.c=.o)

all:	$(NAME)

$(NAME):	$(OBJ) 
	$(CC) $^ -o $@ $(CFLAGS) -o $(NAME)

%.o: %.c  $(INCLD) $(SRC)
	$(CC) $(CFLAGS) -I $(INCLD) -c $< -o $(<:.c=.o)

clean:
	rm -rf $(OBJ) 

fclean: clean
	rm -rf $(NAME)

re: fclean  all

.PHONY : all clean fclean re
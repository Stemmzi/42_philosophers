NAME				=	philo
SRC					=	input_handler.c thread_utils.c init.c cleanup_exit.c philo.c
OBJ					=	$(SRC:.c=.o)
CFLAGS				=	-Wall -Wextra -Werror
CC					=	cc
FSANITIZE			=	-g -fsanitize=address

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(OBJ) -pthread -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $<

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

t: all
	@./$(NAME) 8 500 250 100 5

to: all
	@./$(NAME) 15 500 250 100 5 > output.txt

f: $(OBJ)
	$(CC) $(OBJ) $(FSANITIZE) -pthread -o $(NAME)

re: fclean all

.PHONY: all clean fclean re t

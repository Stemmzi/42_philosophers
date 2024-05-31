NAME				=	philo
SRC					=	input_handler.c thread_utils.c init.c cleanup_exit.c actions.c philo.c
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
	@./$(NAME) 5 800 200 200 7

to: all
	@./$(NAME) 5 800 200 200 7 > output.txt

f: $(OBJ)
	$(CC) $(OBJ) $(FSANITIZE) -pthread -o $(NAME)

re: fclean all

.PHONY: all clean fclean re t

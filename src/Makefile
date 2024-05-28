NAME				=	philo
SRC					=	utils.c input_handler.c init.c philo.c
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
	@./$(NAME) 6 500 120 180 3

f: $(OBJ)
	$(CC) $(OBJ) $(FSANITIZE) -pthread -o $(NAME)

re: fclean all

.PHONY: all clean fclean re t

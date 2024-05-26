NAME				=	philo
SRC					=	utils.c input_handler.c init.c philo.c
OBJ					=	$(SRC:.c=.o)
CFLAGS				=	-Wall -Wextra -Werror
CC					=	cc
FSANITIZE			=	-g -fsanitize=address

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(OBJ) -pthread -o $(NAME)

$(LIBFT):
	$(MAKE) -C libft

%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $<

clean:
	rm -rf obj

fclean: clean
	rm -f $(NAME)

t: all
	@./$(NAME) 5 120 430 180 3

f: $(OBJ)
	$(CC) $(OBJ) $(FSANITIZE) -pthread -o $(NAME)

re: fclean all

.PHONY: all clean fclean re t

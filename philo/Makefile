NAME				=	philo
SRC					=	philo.c
OBJ					=	$(SRC:.c=.o)
CFLAGS				=	-Wall -Wextra -Werror
CC					=	cc

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
	@./$(NAME)

re: fclean all

.PHONY: all clean fclean re t

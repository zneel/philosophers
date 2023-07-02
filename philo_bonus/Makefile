NAME=philo_bonus
CC=cc
CFLAGS=-Wall -Wextra -Werror -pthread -MMD
SRC=	src/main.c \
		src/actions.c \
		src/forks.c \
		src/helpers.c \
		src/philosophers.c \
		src/routine.c \
		src/simulation.c \
		src/time.c \
		src/utils.c


OBJ=$(SRC:.c=.o)
MMD=$(SRC:.c=.d)
LIBRARY=libft/libft.a
INCLUDE=-Iinclude -Ilibft/includes

ifeq ($(SAN),1)
	CFLAGS += -fsanitize=address 
endif

ifeq ($(DEV),1)
	CFLAGS += -g3 -fsanitize=thread
endif

ifeq ($(DEBUG),1)
	CFLAGS += -g3 
endif

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@
all: $(NAME)

$(LIBRARY):
	$(MAKE) -j8 -C libft

$(NAME): $(LIBRARY) $(OBJ)
	$(CC) $(INCLUDE) $(CFLAGS) $(OBJ) $(LIBRARY) -o $(NAME)
clean:
	rm -f $(OBJ) $(MMD)
	$(MAKE) -C libft clean
fclean: clean
	rm -f $(NAME)
	$(MAKE) -C libft fclean
re: fclean all
.PHONY: all clean fclean re
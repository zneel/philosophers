NAME=philo_bonus
CC=cc
CFLAGS=-Wall -Wextra -Werror -pthread -MMD
SRC=	src/main_bonus.c \
		src/philosophers_bonus.c \
		src/helpers_bonus.c \
		src/checker_bonus.c \
		src/forks_bonus.c \
		src/simulation_bonus.c \
		src/routine_bonus.c \
		src/actions_bonus.c \
		src/time_bonus.c \
		src/utils_bonus.c

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
	$(MAKE) -j -C libft

$(NAME): $(LIBRARY) $(OBJ) 
	$(CC) $(CFLAGS) $(OBJ) $(LIBRARY) -o $(NAME)
clean:
	rm -f $(OBJ) $(MMD)
	$(MAKE) -C libft clean
fclean: clean
	rm -f $(NAME)
	$(MAKE) -C libft fclean
re: fclean all
bonus: all
.PHONY: all clean fclean re
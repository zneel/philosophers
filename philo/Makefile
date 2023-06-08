NAME=philo
CC=cc
CFLAGS=-Wall -Wextra -Werror -pthread -MMD
SRC=	src/main.c \
		src/philosophers.c \
		src/helpers.c \
		src/forks.c \
		src/simulation.c \
		src/routine.c \
		src/actions.c \
		src/time.c 

OBJ=$(SRC:.c=.o)
INCLUDE=-Iinclude

ifeq ($(SAN),1)
	CFLAGS += -fsanitize=address 
endif

ifeq ($(DEV),1)
	CFLAGS += -fsanitize=address -g3 
endif

ifeq ($(DEBUG),1)
	CFLAGS += -g3 
endif

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@
all: $(NAME)
$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)
clean:
	rm -f $(OBJ)
fclean: clean
	rm -f $(NAME)
re: fclean all
.PHONY: all clean fclean re
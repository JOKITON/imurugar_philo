NAME = philo

THREAD = -pthread

# /* ~~~~~~~ TESTING FLAGS ~~~~~~~ */
#SANITIZE =
SANITIZE = -g3 -fsanitize=address
#SANITIZE = -g3 -fsanitize=thread

CFLAGS = -Wall -Wextra -Werror -g3 -pthread -Ofast -O3 -march=native $(SANITIZE)

SRCS = main.c \
		utils.c \
		philo.c \
		utils_time.c \
		printer.c \
		die_checker.c \
		cleaner.c

OBJS = $(SRCS:.c=.o)


CC = gcc

all : $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $^ $(THREAD) -o $(NAME)

$(OBJS) : $(SRCS)
	$(CC) $(CFLAGS) -c $(SRCS)


clean :
	rm $(OBJS)

fclean :
	rm $(NAME) $(OBJS)

re : fclean all

.PHONY: all clean fclean re
NAME = philo

THREAD = -pthread

CFLAGS = -Wall -Wextra -Werror -g3 #-fsanitize=pthread

SRCS = main.c \
		utils.c \
		philo.c \
		utils_time.c

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
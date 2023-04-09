NAME = philo
SRCS = main.c libft_utils2.c ft_putstr_fd.c parsing.c show_error.c philosophers.c init.c
OBJS = $(SRCS:%.c=%.o)
CC   = clang
FLAGS = -fsanitize=thread -g
FLAGS = -g
INC = philosophers.h

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(FLAGS) $(OBJS) -o $@

%.o: %.c $(INC)
	$(CC) $(FLAGS) -c $<

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME)

re: fclean all

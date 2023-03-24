NAME = philo
SRCS = main.c libft_utils2.c ft_putstr_fd.c parsing.c
OBJS = $(SRCS:%.c=%.o)
CC   = cc
FLAGS = -Wall -Wextra -fsanitize=address
INC = philosophers.h
all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(FLAGS) $(OBJS) -o $@

%.o: %.c $(INC)
	$(CC) -c $<

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME)

re: fclean all

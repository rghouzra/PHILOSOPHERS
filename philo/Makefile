NAME = philo
SRCS =	main.c\
		libft_utils2.c ft_putstr_fd.c\
		show_error.c memory_cleaner.c\
		parsing.c\
		philosophers.c\
		init.c\
		print_philo_dot.c\
		utils.c\
		routine.c
OBJS = $(SRCS:%.c=%.o)
CC   = cc
FLAGS = -Wall -Wextra -Werror -g
INC = philosophers.h

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(FLAGS) $(OBJS) -o $@

%.o : %.c $(INC)
	$(CC) $(FLAGS) -c $<

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME)

re: fclean all

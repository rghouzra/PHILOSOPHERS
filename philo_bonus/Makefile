NAME = philo_bonus
SRCS =	main.c\
		libft_utils.c ft_putstr_fd.c\
		show_error.c memory_cleaner.c\
		parsing.c\
		philosophers.c\
		init.c\
		utils.c\
		routine.c\
		wrapper_funcs.c\
		semaphore_wrapper.c
OBJS = $(SRCS:%.c=%.o)
CC   = cc
FLAGS = -Wall -Wextra -Werror -pthread
OS := $(shell uname)
ifeq ($(OS),Linux)
	FLAGS += -pthread
endif
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

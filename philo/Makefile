NAME = philo
FILES = init.c philo_check.c philo_mutex.c philo_time.c philo.c
FLAGS = -Wall -Werror -Wextra

all: $(NAME)

$(NAME): $(FILES)
	cc $(FLAGS) $(FILES) -o $(NAME)

clean:
	rm -rf $(NAME)

fclean: clean

re: fclean
SRCS =	philo.c\
 		dinner.c\
		exit.c\
		initialize.c\
		input_validation.c\
		reaper.c\
		take_forks.c\
		utils_functions.c\
		utils_routine.c\

NAME = philo

CC = cc -pthread -fsanitize=thread -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(SRCS)
	@$(CC) $(SRCS) -o $(NAME)

clean:
	@rm -f $(NAME)

re: clean all

fclean: clean

.PHONY: all clean fclean re

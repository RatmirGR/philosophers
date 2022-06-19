NAME = philo_bonus

HEADER = philo.h

FLAGS = -Wall -Wextra -Werror -I $(HEADER)

SRCS = main.c philo.c philo_utils.c observer.c

OBJS = $(patsubst %.c, %.o, $(SRCS))

all : $(NAME)

$(NAME) : $(OBJS)
	gcc $(FLAGS) $(OBJS) -o $(NAME)

%.o : %.c
	gcc $(FLAGS) -c $< -o $@

bonus : all

clean :
	rm -f $(OBJS)

fclean : clean
	rm -f $(NAME)

re : fclean all

.PHONY: all clean fclean re bonus
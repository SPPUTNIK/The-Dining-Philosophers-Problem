NAME = philo

CC = gcc

FLAGS = -Wall -Wextra -Werror

SRC =	philosopher.c\
		ft_checkerr_init_struc.c\
		ft_routin.c\
		ft_atoi.c

all : $(NAME)
$(NAME): $(SRC)
		$(CC) $(FLAGS) $(SRC) -o $(NAME)

clean :
		rm -f $(NAME)

fclean :
		rm -f $(NAME)

re : fclean all

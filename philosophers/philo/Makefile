

CC = cc
FLAGS = -Wall -Wextra -Werror

SRC  = $(wildcard *.c)
OBJ  = $(SRC:.c=.o)
 
NAME = philo

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(FLAGS) $(OBJ) -o $(NAME)

%.o: %.c philo.h
	$(CC) $(FLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)	

fclean: clean
	rm -f $(NAME)

re: fclean all 

.PHONY: all clean fclean re 

42: make ; make clean ; clear
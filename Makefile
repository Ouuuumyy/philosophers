NAME = philo

SRC = 	init.c \
 		main.c \
		parsing.c \
		routine.c \
		utils.c \
		actions.c

OBJ = $(SRC:.c=.o)

FLAGS = -Wall -Werror -Wextra

CC = gcc

all : $(NAME)

$(NAME) : $(OBJ)
		$(CC) $(FLAGS) $(OBJ) -o $(NAME)

clean : 
		rm -f $(OBJ)

fclean : clean
		rm -f $(NAME)

re : fclean all

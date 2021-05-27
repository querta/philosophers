NAME = philo_one
CC = clang
HEADER = header.h
CFLAG = -Wall -Werror -Wextra
SRC = main.c

OBJ = $(SRC:.c=.o)
.PHONY: all, clean, fclean, re

all: $(NAME)

%.o:%.c $(HEADER)
	$(CC) $(CFLAG) -c $< -o $@

$(NAME): $(OBJ)
		$(CC) $(CFLAG) $(OBJ) -o $(NAME)

clean:
	rm -f $(OBJ)

fclean:	clean
	rm -f $(NAME)

re:	fclean all
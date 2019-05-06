##
## EPITECH PROJECT, 2019
## myFTP
## File description:
## Makefile
##

SRC=		src/main.c		\

OBJ=	$(SRC:.c=.o)

NAME	=	myftp

CC	=	gcc

CFLAGS	=	-I./include -Wall -Wextra

all:    $(NAME)

$(NAME):	$(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

tests_run:
	make -C tests

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME) $(OBJ)

re:     fclean all

.PHONY: all clean fclean re tests

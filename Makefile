##
## EPITECH PROJECT, 2019
## myFTP
## File description:
## Makefile
##

SRC=		src/main.c			\
			src/handle_error.c 	\
			src/arpspoof.c 		\
			src/fill_function.c \
			src/get_mac_addr.c 	\
			src/check_func.c 	\
			src/print_struct.c 	\
			src/snd_rcv_func.c


OBJ=	$(SRC:.c=.o)

NAME	=	myARPspoof

CC	=	gcc

CFLAGS	+=	-I./include -Wall -Wextra
# CFLAGS	+=	-I./test_arp -Wall -Wextra

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

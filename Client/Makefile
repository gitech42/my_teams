##
## EPITECH PROJECT, 2020
## Makefille
## File description:
## ...
##

SRC	= 	src/main.c \
		src/login.c \
		src/list.c	\
		src/init.c \
		src/info.c \
		src/create.c \
		src/client_handling.c \
		src/users.c

CC	=	gcc

RM	=	rm -f

CFLAGS	+= -Iinclude -W -Wall -Wextra -g3 -luuid

OBJ	=	$(SRC:.c=.o)

NAME	=	myteams_cli

all : $(NAME)

$(NAME): $(OBJ)
		$(CC) $(OBJ) -L../libs/myteams -lmyteams -o $(NAME) $(CFLAGS)
		mv $(NAME) ../

clean:
		$(RM) $(OBJ)

fclean: clean
		$(RM) ../$(NAME)

re: fclean all

.PHONY: all clean fclean re

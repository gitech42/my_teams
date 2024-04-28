##
## EPITECH PROJECT, 2020
## Makefille
## File description:
## ...
##

SRC	= 	src/main.c	\
		src/struct.c	\
		src/server.c 	\
		src/check_args.c \
		src/client_handling.c	\
		src/utils_2.c	\
		src/username.c	\
		src/commands.c	\
		src/print_data.c	\
		src/found_uuid.c	\
		src/info.c	\
		src/create.c	\
		src/list.c	\
		src/users.c

CC	=	gcc

RM	=	rm -f

CFLAGS	+= -Iinclude -W -Wall -Wextra -g3 -luuid

OBJ	=	$(SRC:.c=.o)

NAME	=	myteams_server

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

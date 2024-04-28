##
## EPITECH PROJECT, 2020
## Makefille
## File description:
## ...
##

all: serv cli

cli:
	make -C Client/

serv: 
	make -C Server/

clean:
	make -C Client/ clean
	make -C Server/ clean

fclean:
	make -C Client/ fclean
	make -C Server/ fclean

re: fclean all

.PHONY: all clean fclean re

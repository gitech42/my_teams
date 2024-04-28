/*
** EPITECH PROJECT, 2022
** B-NWP-400-PAR-4-1-myteams-sacha.lliso
** File description:
** check_args
*/

#include "teams.h"

static const char help[] = "USAGE: ./myteams_server port\
            \n\tport is the port number on which the server socket listens\n";

int check_args(int ac, char *av[])
{
    if (ac > 2 || ac < 2) {
        printf("%s\n", help);
        return 84;
    } else if (!(strcmp(av[1], "-help"))) {
        printf("%s\n", help);
        return 1;
    } if (atoi(av[1]) <= 0) {
        printf("Port cannot be <= 0");
        return 84;
    }
    return 0;
}

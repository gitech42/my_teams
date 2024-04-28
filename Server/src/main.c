/*
** EPITECH PROJECT, 2022
** B-NWP-400-PAR-4-1-myteams-sacha.lliso
** File description:
** main
*/

#include "teams.h"

int close_socket(int *socketfd)
{
    if (close((*socketfd)) == - 1) {
        perror("close_socket");
        return -1;
    }
    (*socketfd) = -1;
    return 0;
}

int main(int ac, char *av[])
{
    struct c_l clients;
    struct te_l teams;

    if (check_args(ac, av) == 0) {

        LIST_INIT(&clients);
        LIST_INIT(&teams);
        launch_server(av, &clients, &teams);
        return 0;
    }
    return 84;
}

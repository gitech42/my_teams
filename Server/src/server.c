/*
** EPITECH PROJECT, 2022
** B-NWP-400-PAR-4-1-myteams-sacha.lliso
** File description:
** server
*/

#include "teams.h"

struct timeval set_timeval(void)
{
    struct timeval tv;

    tv.tv_sec = 1;
    tv.tv_usec = 0;
    return tv;
}

int set_fdSet(int sockfd, fd_set *fdset, struct timeval *tv, struct c_l *c)
{
    int fds = sockfd;
    client_t *cli;

    *tv = set_timeval();
    FD_ZERO(fdset);
    FD_SET(sockfd, fdset);

    LIST_FOREACH(cli, c, ptr) {
        if (cli->fd > 0) {
            FD_SET(cli->fd, fdset);
            if (fds < cli->fd)
                fds = cli->fd;
        }
    }
    return fds;
}

void launch_server(char *av[], struct c_l *clients, struct te_l *team)
{
    server_t server = init_server_struct(av);
    struct timeval tv = set_timeval();
    int retval;
    int maxfd = server.fd;
    client_t *tmp;

    LIST_FOREACH(tmp, clients, ptr);
    for (int i = 0; 1; ++i) {
        maxfd = set_fdSet(server.fd, &server.rfds, &tv, clients);
        retval = select(maxfd + 1, &server.rfds, NULL, NULL, NULL);
        if (retval == -1)
            perror("select()");
        else if (retval) {
            if (FD_ISSET(server.fd, &server.rfds)) {
                get_client(&server, clients);
            }
            handle_client(server, clients, team);
        }
    }
    close_socket(&server.fd);
}

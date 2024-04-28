/*
** EPITECH PROJECT, 2022
** B-NWP-400-PAR-4-1-myteams-sacha.lliso
** File description:
** client_handling
*/

#include "teams.h"

int get_client(server_t *server, struct c_l *clients)
{
    client_t *client = malloc(sizeof(client_t));
    int size = sizeof(client->addr);

    client->fd = accept(server->fd, (struct sockaddr *)&client->addr
        , (unsigned int *)&size);
    if (client->fd < 0) {
        perror("accept");
        return 84;
    } else if (client->fd > 0) {
        client = init_client(client);
        LIST_INSERT_HEAD(clients, client, ptr);
    }
    return 0;
}

void manage_cmd(client_t *client, struct c_l *cli, struct te_l *tm)
{
    int len = 0;
    char buff[256];

    if ((len = read(client->fd, buff, sizeof(buff))) < 0) {
        exit(0);
    } else if (len > 0) {
        buff[len] = 0;
        exec_cmd(buff, client, cli, tm);
    } else
        close_socket(&client->fd);
}

int handle_client(server_t server, struct c_l *cli, struct te_l *tm)
{
    client_t *client = NULL;

    LIST_FOREACH(client, cli, ptr) {
        if (FD_ISSET(client->fd, &server.rfds)) {
            manage_cmd(client, cli, tm);
            return 0;
        }
    }
    return 0;
}

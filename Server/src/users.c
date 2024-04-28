/*
** EPITECH PROJECT, 2022
** B-NWP-400-PAR-4-1-myteams-sacha.lliso
** File description:
** users
*/

#include "teams.h"

void users_command(client_t *client, struct c_l *c)
{
    client_t *tmp = NULL;

    LIST_FOREACH(tmp, c, ptr) {
        if (uuid_compare(tmp->uuid, client->uuid) == 0)
            continue;
        print_info_user(tmp, client->fd, "users");
    }
}

void user_command(client_t *client, struct c_l *c)
{
    char *tmp = strtok(NULL, " \"\n\0");
    client_t *cli_tmp = NULL;

    if (!tmp)
        return;
    cli_tmp = found_cli_by_uuid(tmp, c);
    if (!cli_tmp) {
        return;
    }
    print_info_user(cli_tmp, client->fd, "user");
}

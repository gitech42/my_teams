/*
** EPITECH PROJECT, 2022
** B-NWP-400-PAR-4-1-myteams-sacha.lliso
** File description:
** info
*/

#include "client.h"


void info(cli_t *cli)
{
    char uuid[36];

    uuid_unparse(cli->uuid, uuid);
    client_print_user(uuid, cli->username, 1);
}

void info_teams()
{
    char *name = strtok(NULL, "$\"\n");
    char *uuid = strtok(NULL, "$\"\n");
    char *desc = strtok(NULL, "$\"\n");

    client_print_team(uuid, name, desc);
}

void info_channel()
{
    char *name = strtok(NULL, "$\"\n");
    char *uuid = strtok(NULL, "$\"\n");
    char *desc = strtok(NULL, "$\"\n");

    client_print_channel(uuid, name, desc);
}

void info_thread()
{
}

void info_signal(cli_t *cli)
{
    if (cli->used_enum == TEAMS) {
        info_teams();
    } else if (cli->used_enum == CHANNELS) {
        info_channel();
    } else if (cli->used_enum == THREADS) {
        info_thread();
    }
}
/*
** EPITECH PROJECT, 2022
** B-NWP-400-PAR-4-1-myteams-sacha.lliso
** File description:
** list
*/

#include "client.h"

void list_teams()
{
    char *name = strtok(NULL, "$\"\n");
    char *uuid = strtok(NULL, "$\"\n");
    char *desc = strtok(NULL, "$\"\n");

    client_print_teams(uuid, name, desc);
}

void list_channel()
{
    char *name = strtok(NULL, "$\"\n");
    char *uuid = strtok(NULL, "$\"\n");
    char *desc = strtok(NULL, "$\"\n");

    client_team_print_channels(uuid, name, desc);
}

void list_thread()
{
}

void list_signal(cli_t *cli)
{
    if (cli->used_enum == NOTHING) {
        list_teams();
    } else if (cli->used_enum == TEAMS) {
        list_channel();
    } else if (cli->used_enum == CHANNELS) {
        list_thread();
    } else if (cli->used_enum == THREADS) {
        return;
    }
}
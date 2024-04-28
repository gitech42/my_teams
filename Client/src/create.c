/*
** EPITECH PROJECT, 2022
** B-NWP-400-PAR-4-1-myteams-sacha.lliso
** File description:
** create
*/

#include "client.h"

void get_message()
{
    char *uuid = strtok(NULL, " \"\n");
    char *body = strtok(NULL, "\"\n");

    client_event_private_message_received(uuid, body);
}

void create_teams(int fd)
{
    char *name = strtok(NULL, "\"\n");
    char *desc = strtok(NULL, "\n");
    desc+=2;
    desc[strlen(desc)- 1] = '\0';
    uuid_t uuid;
    char tmp_uuid[36];

    uuid_generate(uuid);
    uuid_unparse(uuid, tmp_uuid);
    dprintf(fd, "/create %s$%s$%s\n", name, desc, tmp_uuid);
    client_event_team_created(tmp_uuid, name, desc);
    client_print_team_created(tmp_uuid, name, desc);
}

void create_channel(int fd)
{
    char *name = strtok(NULL, "\"\n");
    char *desc = strtok(NULL, "\n");
    desc+=2;
    desc[strlen(desc)- 1] = '\0';
    char tmp_uuid[36];
    uuid_t uuid;

    uuid_generate(uuid);
    uuid_unparse(uuid, tmp_uuid);
    dprintf(fd, "/create %s$%s$%s\n", name, desc, tmp_uuid);
    client_event_channel_created(tmp_uuid, name, desc);
    client_print_channel_created(tmp_uuid, name, desc);
}

void create_thread()
{
}

void create_signal(cli_t *cli, int fd, char *cmd)
{
    strtok(cmd, " \"\n\t");
    if (cli->used_enum == NOTHING) {
        create_teams(fd);
    } else if (cli->used_enum == TEAMS) {
        create_channel(fd);
    } else if (cli->used_enum == CHANNELS) {
        create_thread();
    } else if (cli->used_enum == THREADS) {
        return;
    }
}
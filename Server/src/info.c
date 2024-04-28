/*
** EPITECH PROJECT, 2022
** B-NWP-400-PAR-4-1-myteams-sacha.lliso
** File description:
** info
*/

#include "teams.h"

void info_teams(client_t *client, struct te_l *t)
{
    teams_t *tmp = NULL;

    LIST_FOREACH(tmp, t, ptr) {
        if (uuid_compare(client->used_uuid, tmp->uuid) == 0)
            print_info_team(tmp, client->fd, "info");
    }
}

void info_channel(client_t *client, struct te_l *t)
{
    channel_t *tmp = NULL;
    char *tmp_uuid = NULL;
    teams_t *tmp_teams = NULL;

    uuid_unparse(client->used_uuid, tmp_uuid);
    tmp_teams = found_teams_by_uuid(tmp_uuid, t);
    LIST_FOREACH(tmp, &tmp_teams->channels, ptr) {
        if (uuid_compare(client->used_uuid, tmp->uuid) == 0)
            print_info_channel(tmp, client->fd, "info");
    }
}

void info_thread(client_t *client, struct te_l *t)
{
    thread_t *tmp = NULL;
    char *tmp_uuid = NULL;
    teams_t *tmp_t = NULL;
    channel_t *tmp_channel = NULL;

    uuid_unparse(client->used_uuid, tmp_uuid);
    tmp_t = found_teams_by_uuid(tmp_uuid, t);
    LIST_FOREACH(tmp_channel, &tmp_t->channels, ptr) {
        LIST_FOREACH(tmp, &tmp_channel->threads, ptr) {
            if (uuid_compare(client->used_uuid, tmp->uuid) == 0)
                print_info_threads(tmp, client->fd, "info");
        }
    }
}

void info_command(client_t *client, struct te_l *t)
{
    if (client->used_enum == TEAMS) {
        info_teams(client, t);
    } else if (client->used_enum == CHANNELS) {
        info_channel(client, t);
    } else if (client->used_enum == THREADS) {
       info_thread(client, t);
    }
}

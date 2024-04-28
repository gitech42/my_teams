/*
** EPITECH PROJECT, 2022
** B-NWP-400-PAR-4-1-myteams-sacha.lliso
** File description:
** list
*/

#include "teams.h"

void list_reply(client_t *client)
{
    (void) client;
}

void list_teams(client_t *client, struct te_l *t)
{
    teams_t *tmp = NULL;

    if (LIST_EMPTY(t)) {
        dprintf(client->fd, "No such teams\n");
        return;
    }
    LIST_FOREACH(tmp, t, ptr) {
        print_info_team(tmp, client->fd, "list");
    }
}

void list_channels(client_t *client)
{
    channel_t *tmp = NULL;
    teams_t *tmp_teams = (teams_t *) client->current_used;

    LIST_FOREACH(tmp, &tmp_teams->channels, ptr) {
        print_info_channel(tmp, client->fd, "list");
    }
}

void list_threads(client_t *client)
{
    thread_t *tmp = NULL;
    channel_t *tmp_chan = (channel_t *) client->current_used;

    LIST_FOREACH(tmp, &tmp_chan->threads, ptr) {
        print_info_threads(tmp, client->fd, "list");
    }
}

void list_command(client_t *client, struct te_l *t)
{
    if (client->used_enum == NOTHING) {
        list_teams(client, t);
    } else if (client->used_enum == TEAMS) {
        list_channels(client);
    } else if (client->used_enum == CHANNELS) {
        list_threads(client);
    } else if (client->used_enum == THREADS) {
        list_reply(client);
    }
}

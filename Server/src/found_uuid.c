/*
** EPITECH PROJECT, 2022
** B-NWP-400-PAR-4-1-myteams-sacha.lliso
** File description:
** found_uuid
*/

#include "teams.h"

bool compare_uuid(const char *uuid_cmp, uuid_t uuid)
{
    uuid_t cmp1;

    uuid_parse(uuid_cmp, cmp1);
    if (uuid_compare(cmp1, uuid) == 0)
        return true;
    return false;
}

client_t *found_cli_by_uuid(const char *uuid, struct c_l *clients)
{
    client_t *client = NULL;

    LIST_FOREACH(client, clients, ptr) {
        if (compare_uuid(uuid, client->uuid))
            return client;
    }
    printf("Couldn't find user with uuid\n");
    return NULL;
}

teams_t *found_teams_by_uuid(const char *uuid, struct te_l *teams)
{
    teams_t *team = NULL;

    LIST_FOREACH(team, teams, ptr) {
        if (compare_uuid(uuid, team->uuid))
            return team;
    }
    printf("It's not a team...\n");
    return NULL;
}

channel_t *found_channel_by_uuid(const char *uuid, struct te_l *teams)
{
    channel_t *chan = NULL;
    teams_t *tmp = NULL;

    LIST_FOREACH(tmp, teams, ptr) {
        LIST_FOREACH(chan, &tmp->channels, ptr) {
            if (compare_uuid(uuid, chan->uuid))
                return chan;
        }
    }
    printf("It's not a channel...\n");
    return NULL;
}

thread_t *found_thread_by_uuid(const char *uuid, struct te_l *teams)
{
    thread_t *thread = NULL;
    teams_t *tmp = NULL;
    channel_t *chan = NULL;

    LIST_FOREACH(tmp, teams, ptr) {
        LIST_FOREACH(chan, &tmp->channels, ptr) {
            LIST_FOREACH(thread, &chan->threads, ptr) {
                if (compare_uuid(uuid, thread->uuid))
                    return thread;
            }
        }
    }
    printf("It's not a threads...\n");
    return NULL;
}

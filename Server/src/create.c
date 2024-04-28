/*
** EPITECH PROJECT, 2022
** B-NWP-400-PAR-4-1-myteams-sacha.lliso
** File description:
** create
*/

#include "teams.h"

void create_teams(client_t *client, struct te_l *t)
{
    teams_t *new = NULL;
    char *name = strdup(strtok(NULL, "$\n"));
    char *desc = strdup(strtok(NULL, "$\n"));
    char *uuid = strdup(strtok(NULL, "$\n"));

    if (!name)
        return;
    if (!desc) {
        if (name)
            free(name);
        return;
    }
    new = init_teams(name, desc, client->uuid, uuid);
    LIST_INSERT_HEAD(t, new, ptr);
}

void create_channel(client_t *client)
{
    channel_t *new = NULL;
    char *name = strdup(strtok(NULL, "$\n"));
    char *desc = strdup(strtok(NULL, "$\n"));
    char *chann_uuid = strdup(strtok(NULL, "$\n"));
    teams_t *tmp = (teams_t *)client->current_used;

    if (!tmp) {
        return;
    }
    if (!name)
        return;
    if (!desc) {
        if (name)
            free(name);
        return;
    }
    new = init_channel(name, desc, client->used_uuid, chann_uuid);
    LIST_INSERT_HEAD(&tmp->channels, new, ptr);
}

void create_thread(client_t *client)
{
    thread_t *new = NULL;
    char *title = strdup(strtok(NULL, "$\n"));
    char *msg = strdup(strtok(NULL, "$\n"));
    char *uuid = strdup(strtok(NULL, "$\n"));
    channel_t *tmp = (channel_t *) client->current_used;

    if (!title)
        return;
    if (!msg) {
        if (title)
            free(title);
        return;
    }
    new = init_thread(title, msg, client->used_uuid, client->uuid, uuid);
    LIST_INSERT_HEAD(&tmp->threads, new, ptr);
}

void create_reply()
{
    return;
}

void create_command(client_t *client, struct te_l *t)
{
    if (client->used_enum == NOTHING) {
        create_teams(client, t);
    } else if (client->used_enum == TEAMS) {
        create_channel(client);
    } else if (client->used_enum == CHANNELS) {
       create_thread(client);
    } else if (client->used_enum == THREADS) {
        create_reply();
    }
}
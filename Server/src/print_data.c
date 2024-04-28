/*
** EPITECH PROJECT, 2022
** B-NWP-400-PAR-4-1-myteams-sacha.lliso
** File description:
** print_data
*/

#include "teams.h"

void print_info_user(client_t *client, int fd, char *cmd)
{
    char uuid[36];

    uuid_unparse(client->uuid, uuid);
    dprintf(fd, "%s %s %s\n", cmd, client->username, uuid);
}

void print_info_team(teams_t *team, int fd, char *cmd)
{
    char uuid[36];

    if (!team)
        return;
    uuid_unparse(team->uuid, uuid);
    dprintf(fd, "%s %s$%s$%s\n", cmd, team->name, uuid,
        team->description);
}

void print_info_channel(channel_t *chan, int fd, char *cmd)
{
    char uuid[36];

    if (!chan)
        return;
    uuid_unparse(chan->uuid, uuid);
    dprintf(fd, "%s %s$%s$%s\n", cmd, chan->name, uuid,
        chan->description);
}

void print_info_threads(thread_t *thrd, int fd, char *cmd)
{
    char uuid[36];

    if (!thrd)
        return;
    uuid_unparse(thrd->uuid, uuid);
    dprintf(fd, "%s %s$%s$%s\n", cmd, thrd->title, uuid,
        thrd->message);
}

void print_info_reply(thread_t *reply, int fd, char *cmd)
{
    char uuid[36];

    if (!reply)
        return;
    uuid_unparse(reply->uuid, uuid);
    dprintf(fd, "%s %s$%s$%s\n", cmd, reply->title, uuid,
        reply->message);
}


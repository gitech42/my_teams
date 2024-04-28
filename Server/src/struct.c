/*
** EPITECH PROJECT, 2022
** B-NWP-400-PAR-4-1-myteams-sacha.lliso
** File description:
** struct
*/

#include "teams.h"

thread_t *init_thread(char *title, char *msg, uuid_t chan_uuid,
uuid_t user_uuid, char *uuid)
{
    thread_t *tmp = malloc(sizeof(thread_t));
    char temp_channel_uuid[36];
    char temp_user_uuid[36];

    tmp->title = title;
    tmp->message = msg;
    uuid_copy(tmp->channel_uuid, chan_uuid);
    uuid_copy(tmp->creator_uuid, user_uuid);
    uuid_unparse(tmp->channel_uuid, temp_channel_uuid);
    uuid_unparse(user_uuid, temp_user_uuid);
    uuid_parse(uuid, tmp->uuid);
    server_event_thread_created(temp_channel_uuid, uuid, temp_user_uuid,
        tmp->title,tmp->message);
    return tmp;
}

channel_t *init_channel(char *name, char *desc, uuid_t team_uuid, char *uuid)
{
    channel_t *tmp = malloc(sizeof(channel_t));
    char temp_team_uuid[36];

    LIST_INIT(&tmp->threads);
    tmp->name = name;
    tmp->description = desc;
    uuid_copy(tmp->team_uuid, team_uuid);
    uuid_parse(uuid, tmp->uuid);
    uuid_unparse(tmp->team_uuid, temp_team_uuid);
    server_event_channel_created(temp_team_uuid,
        uuid, tmp->name);
    return tmp;
}

teams_t *init_teams(char *name, char *description, uuid_t c_uuid, char *uuid)
{
    teams_t *tmp = malloc(sizeof(teams_t));
    char tmp_user_uuid[36];

    LIST_INIT(&tmp->channels);
    tmp->name = name;
    tmp->description = description;
    uuid_copy(tmp->uuid_creator, c_uuid);
    uuid_unparse(tmp->uuid_creator, tmp_user_uuid);
    uuid_parse(uuid, tmp->uuid);
    server_event_team_created(uuid, tmp->name, tmp_user_uuid);
    return tmp;
}

client_t *init_client(client_t *cli)
{
    cli->ip = NULL;
    cli->username = NULL;
    cli->used_enum = NOTHING;
    uuid_clear(cli->uuid);
    uuid_clear(cli->used_uuid);
    cli->current_used = NULL;
    return cli;
}

server_t init_server_struct(char *av[])
{
    server_t server;

    server.port = atoi(av[1]);
    server.fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server.fd == -1) {
        perror("socket");
        exit(84);
    }
    server.addr.sin_family = AF_INET;
    server.addr.sin_port = htons(server.port);
    server.addr.sin_addr.s_addr = 0;
    if (bind(server.fd, (struct sockaddr *) &server.addr,
                             sizeof(server.addr)) == - 1)
        exit(84);
    if (listen(server.fd, SOMAXCONN) == -1)
        exit(84);
    return server;
}

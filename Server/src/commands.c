/*
** EPITECH PROJECT, 2022
** B-NWP-400-PAR-4-1-myteams-sacha.lliso
** File description:
** commands
*/

#include "teams.h"

void send_command(client_t *client, struct c_l *clients, char *buff)
{
    char *target_uuid = strtok(NULL, " \"");
    char *body = strtok(buff, " ");
    body = strtok(NULL, " ");
    body = strtok(NULL, ("\"\n"));
    client_t *tmp_cli = NULL;
    char tmp_cli_2[36];
    char tmp_cli_1[36];

    if (!target_uuid)
        return;
    tmp_cli = found_cli_by_uuid(target_uuid, clients);
    if (!tmp_cli) {
        dprintf(client->fd, "%s does not exist\n", target_uuid);
        return;
    }
    if (!target_uuid)
        return;
    uuid_unparse(client->uuid, tmp_cli_1);
    uuid_unparse(tmp_cli->uuid, tmp_cli_2);
    dprintf(tmp_cli->fd, "msg %s %s", tmp_cli_1, body);
    server_event_private_message_sended(tmp_cli_1, tmp_cli_2, body);
}

void use_command(client_t *client, struct te_l *t)
{
    char *tmp = strtok(NULL, " \n\"\0");

    if (!tmp) {
        client->used_enum = NOTHING;
        return;
    }
    uuid_parse(tmp, client->used_uuid);
    if ((client->current_used = found_teams_by_uuid(tmp, t)) != NULL) {
        client->used_enum = TEAMS;
    } else if ((client->current_used = found_channel_by_uuid(tmp, t))) {
        client->used_enum = CHANNELS;
    } else if ((client->current_used = found_thread_by_uuid(tmp, t))) {
        client->used_enum = THREADS;
    }
    dprintf(client->fd, "use %d", client->used_enum);
}

void logout_client(client_t *client)
{
    char uuid[36];

    uuid_unparse(client->uuid, uuid);
    server_event_user_logged_out(uuid);
    free(client->username);
    client->username = NULL;
}

void exec_cmd_1(char *cmd, client_t *client, struct te_l *t)
{
    if (strcmp(cmd, "/create") == 0) {
        create_command(client, t);
    } else if (strcmp(cmd, "/logout") == 0) {
        logout_client(client);
    } else if (strcmp(cmd, "/list") == 0) {
        list_command(client, t);
    }
}

void exec_cmd(char *buff, client_t *client, struct c_l *c, struct te_l *t)
{
    char *copy = strdup(buff);
    char *cmd = strtok(buff, " \n\0");

    if (cmd == NULL)
        return;
    if ((strcmp(cmd, "/login")) == 0 && client->username == NULL) {
        new_connection(client);
    } else if (strcmp(cmd, "/help") == 0)
        help_message(client->fd);
    if (!client->username)
        return;
    if (strcmp(cmd, "/send") == 0) {
        send_command(client, c, copy);
    } else if (strcmp(cmd, "/info") == 0) {
        info_command(client, t);
    } else if (strcmp(cmd, "/user") == 0) {
        user_command(client, c);
    } else if (strcmp(cmd, "/users") == 0) {
        users_command(client, c);
    } else if (strcmp(cmd, "/use") == 0) {
        use_command(client, t);
    } else
        exec_cmd_1(cmd, client, t);
}

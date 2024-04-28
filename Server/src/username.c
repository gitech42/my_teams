/*
** EPITECH PROJECT, 2022
** B-NWP-400-PAR-4-1-myteams-sacha.lliso
** File description:
** username
*/

#include "teams.h"

int get_username(client_t *client)
{
    char *temp = NULL;

    client->username = strdup(strtok(NULL, " \"\n\t"));
    temp = strtok(NULL, " \"\n\t");
    uuid_parse(temp, client->uuid);
    return 0;
}

int check_already_exist(client_t *client)
{
    int i = 1;
    char *temp = NULL;
    FILE *file = fopen("./Server/user.txt", "r");
    char buff[256];

    while(fgets(buff, sizeof(buff), file)) {
        temp = strdup(strtok(buff, " \"\n"));
        if ((strcmp(temp, client->username)) == 0) {
            fclose(file);
            return 0;
        }
        i++;
    }
    fclose(file);
    return i;
}

int stock_username_in_file(client_t *client)
{
    FILE *filefd = fopen("./Server/user.txt", "a+");
    char tmp_uuid[36];

    fprintf(filefd,"%s\n",client->username);
    if (check_already_exist(client) == 0)
        return 0;
    uuid_unparse(client->uuid, tmp_uuid);
    server_event_user_created(tmp_uuid, client->username);
    fclose(filefd);
    return 1;
}

void new_connection(client_t *client)
{
    char uuid[36];

    get_username(client);
    stock_username_in_file(client);
    uuid_unparse(client->uuid, uuid);
    server_event_user_logged_in(uuid);
}
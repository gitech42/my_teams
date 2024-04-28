/*
** EPITECH PROJECT, 2022
** B-NWP-400-PAR-4-1-myteams-sacha.lliso
** File description:
** utils_2
*/

#include "teams.h"

void help_message(int fd)
{
    dprintf(fd, "/login [“user_name”]\n/logout\n/users\n"
    "/user [“user_uuid”]\n/send [“user_uuid”] [“message_body”]\n"
    "/messages [“user_uuid”]\n/subscribe [“team_uuid”]\n"
    "/subscribed ?[“team_uuid”]\n/unsubscribe [“team_uuid”]\n"
    "/use ?[“team_uuid”] ?[“channel_uuid”] ?[“thread_uuid”]\n"
    "/create\n/list\n/info\n");
}

void clear_client_struct(client_t *client)
{
    if (client->username)
        free(client->username);
}

char *read_file(char *file)
{
    int fd = open(file, O_RDONLY);
    int fd_sz = 0;
    char *buff = NULL;
    struct stat sb;

    if (fd == -1)
        return buff;
    fstat(fd, &sb);
    fd_sz = sb.st_size;
    buff = malloc(sizeof(char) * (fd_sz + 1));
    read(fd, buff, fd_sz);
    buff[fd_sz] = '\0';
    close(fd);
    return buff;
}

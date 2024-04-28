/*
** EPITECH PROJECT, 2022
** B-NWP-400-PAR-4-1-myteams-sacha.lliso
** File description:
** client_handling
*/

#include "client.h"

void check_received_message(int srvfd, cli_t *cli)
{
    int length = 0;
    char buff[516];
    char *tmp = NULL;

    length = read(srvfd, buff, sizeof(buff));
    buff[length] = 0;
    tmp = strtok(buff, " \"\n");
    if (tmp) {
        if (strcmp(tmp, "use") == 0) {
            cli->used_enum = atoi(strtok(NULL, " \n"));
        } else if (strcmp(tmp, "list") == 0) {
            list_signal(cli);
        } else if (strcmp(tmp, "info") == 0) {
            info_signal(cli);
        } else if (strcmp(tmp, "msg") == 0) {
            get_message();
        } else if (strcmp(tmp, "user") == 0) {
            user_cmd();
        } else if (strcmp(tmp, "users") == 0) {
            users_cmd();
        }
    }
}

void use_cmd(char *buff, cli_t *cli, int srvfd)
{
    char *tmp = NULL;
    uuid_t uuid;

    tmp = strtok(buff, " \"\n\t");
    tmp = strtok(NULL, " \"\n\t");
    if (tmp) {
        uuid_parse(tmp, uuid);
        uuid_copy(cli->used_uuid, uuid);
        dprintf(srvfd, "/use %s", tmp);
    } else {
        dprintf(srvfd, "/use ");
        cli->used_enum = NOTHING;
    }
    return;
}

void sigint_handler(int sig)
{
    exit(0);
}

void handle_cli(int clifd, int servfd, cli_t *cli)
{
    fd_set rfds;
    int retval = 0;

    signal(SIGINT, sigint_handler);
    while (1) {
        FD_ZERO(&rfds);
        FD_SET(clifd, &rfds);
        FD_SET(servfd, &rfds);
        if ((retval = select(servfd + 1, &rfds, NULL, NULL, NULL)) == -1) {
            perror("select");
        } else if (retval) {
            select_action(clifd, servfd, &rfds, cli);
        }
    }
}

int connect_cli(char *av[], cli_t *cli)
{
    struct sockaddr_in addr;
    int fd = -1;
    int clifd = 0;

    fd = socket(AF_INET, SOCK_STREAM, 0);
    addr.sin_family = AF_INET;
    addr.sin_port = htons(atoi(av[2]));
    addr.sin_addr.s_addr = inet_addr(av[1]);
    if ((clifd = connect(fd, (struct sockaddr *) &addr, sizeof(addr))) == - 1)
        perror("connect");
    init_cli(cli);
    handle_cli(clifd, fd, cli);
    return 0;
}
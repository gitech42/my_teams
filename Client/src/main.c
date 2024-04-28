/*
** EPITECH PROJECT, 2022
** B-NWP-400-PAR-4-1-myteams-sacha.lliso
** File description:
** main
*/

#include "client.h"

static const char help[] = "USAGE: ./myteams_cli ip port\
            \n\tip is the server ip address on which the server socket listens\
            \n\tport is the port number on which the server socket listens";

char *handle_login_command(char *buff, cli_t *cli)
{
    char *cmd_with_uuid = NULL;
    char tmp_uuid[36];
    char *cmd = NULL;
    char *dup = strdup(buff);


    strtok(dup, " \"\n");
    cli->username = strdup(strtok(NULL, " \"\n"));
    uuid_unparse(cli->uuid, tmp_uuid);
    cmd = strtok(buff, "\n");
    cmd_with_uuid = strcat(cmd, " ");
    cmd_with_uuid = strcat(cmd_with_uuid, tmp_uuid);
    cmd_with_uuid[strlen(cmd_with_uuid)] = 0;
    client_event_logged_in(tmp_uuid, cli->username);
    free(dup);
    return cmd_with_uuid;
}

char *check_login(char *buff, cli_t *cli, int srvfd)
{
    char *tmp = NULL;
    char tmp_uuid[36];

    if (strncmp("/use ", buff, 5) == 0) {
        use_cmd(buff, cli, srvfd);
        return NULL;
    } else if ((strncmp("/login ", buff, 7)) == 0) {
        tmp = handle_login_command(buff, cli);
    } else if (strncmp("/logout", buff, 7) == 0 && cli->username) {
        uuid_unparse(cli->uuid, tmp_uuid);
        client_event_logged_out(tmp_uuid, cli->username);
    } else if (strncmp(buff, "/create", 7) == 0 && cli->username) {
        create_signal(cli, srvfd, buff);
        return NULL;
    } else if (strncmp(buff, "/info", 5) == 0 && cli->username) {
        strtok(buff, " \n");
        if (!strtok(NULL, " \"\n"))
            info(cli);
    }
    return tmp ? tmp : buff;
}

void select_action(int clifd, int srvfd, fd_set *rfds, cli_t *cli)
{
    char buff[516];
    int length = 0;
    char *temp = NULL;

    if (FD_ISSET(clifd, rfds)) {
        length = read(clifd, buff, sizeof(buff));
        if (length < 0)
            exit(0);
        buff[length] = 0;
        temp = check_login(buff, cli, srvfd);
        if (temp)
            send(srvfd, temp, strlen(temp), 0);
    } else if (FD_ISSET(srvfd, rfds)) {
        check_received_message(srvfd, cli);
    }
    FD_CLR(srvfd, rfds);
}

int check_args(int ac, char *av[])
{
    if (ac != 3) {
        printf("%s\n", help);
        return 84;
    } else if (!(strcmp(av[1], "-help"))) {
        printf("%s\n", help);
        return 1;
    }
    return 0;
}

int main(int ac, char *av[])
{
    cli_t cli;

    if (check_args(ac, av) == 0) {
        return connect_cli(av, &cli);
    }
    return 84;
}

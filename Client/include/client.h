/*
** EPITECH PROJECT, 2022
** B-NWP-400-PAR-4-1-myteams-sacha.lliso
** File description:
** client
*/

#ifndef CLIENT_H_
#define CLIENT_H_
#include "logging_client.h"
#include <stdio.h>
#include <uuid/uuid.h>
#include <sys/socket.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include <signal.h>
#include <stdbool.h>
typedef enum enum_e {
    NOTHING,
    TEAMS,
    CHANNELS,
    THREADS
}enum_t ;

typedef struct cli_s {
        char *username;
        uuid_t uuid;
        uuid_t used_uuid;
        enum_t used_enum;
        void *current_used;
} cli_t;

cli_t *init_cli(cli_t *cli);
void list_signal(cli_t *cli);
void info_signal(cli_t *cli);
void create_signal(cli_t *cli, int fd, char *cmd);
void handle_cli(int clifd, int servfd, cli_t *cli);
int connect_cli(char *av[], cli_t *cli);
void get_message();
void select_action(int clifd, int srvfd, fd_set *rfds, cli_t *cli);
void check_received_message(int srvfd, cli_t *cli);
void use_cmd(char *buff, cli_t *cli, int srvfd);
void info(cli_t *cli);
void user_cmd();
void users_cmd();
#endif /* !CLIENT_H_ */

/*
** EPITECH PROJECT, 2022
** B-NWP-400-PAR-4-1-myteams-sacha.lliso
** File description:
** teams
*/

#ifndef TEAMS_H_
    #define TEAMS_H_
    #include "uuid/uuid.h"
    #include "logging_server.h"
    #include <sys/socket.h>
    #include <sys/time.h>
    #include <sys/types.h>
    #include <sys/select.h>
    #include <sys/stat.h>
    #include <sys/queue.h>
    #include <sys/mman.h>
    #include <netinet/in.h>
    #include <netinet/ip.h>
    #include <arpa/inet.h>
    #include <fcntl.h>
    #include <netdb.h>
    #include <stdbool.h>
    #include <stdio.h>
    #include <string.h>
    #include <unistd.h>
    #include <stdlib.h>
    #define MAX_CLIENTS 100
    #define MAX_NAME_LENGTH 32
    #define MAX_DESCRIPTION_LENGTH 255
    #define MAX_BODY_LENGTH 512

    typedef struct server_s {
        int port;
        int fd;
        char *ip;
        fd_set rfds;
        fd_set wfds;
        fd_set efds;
        struct sockaddr_in addr;
    } server_t;

    typedef enum used_e {
        NOTHING,
        TEAMS,
        CHANNELS,
        THREADS
    }used_t ;

    typedef struct client_s {
        int fd;
        char *ip;
        char *username;
        uuid_t uuid;
        used_t used_enum;
        uuid_t used_uuid;
        struct sockaddr_in addr;
        void *current_used;
        LIST_ENTRY(client_s) ptr;
    } client_t;

    LIST_HEAD(c_l, client_s);

    typedef struct thread_s {
        char *title;
        char *message;
        uuid_t uuid;
        uuid_t channel_uuid;
        uuid_t creator_uuid;
        uuid_t *users_uuid;
        LIST_ENTRY(thread_s) ptr;
    } thread_t;

    LIST_HEAD(th_l, thread_s);

    typedef struct channel_s {
        char *name;
        char *description;
        uuid_t team_uuid;
        uuid_t uuid;
        uuid_t *threads_uuid;
        uuid_t *users_uuid;
        struct th_l threads;
        LIST_ENTRY(channel_s) ptr;
    } channel_t;

    LIST_HEAD(ch_l, channel_s);

 typedef struct teams_s {
        uuid_t uuid;
        char *name;
        char *description;
        uuid_t *channel_uuid;
        uuid_t *users_uuid;
        uuid_t uuid_creator;
        struct ch_l channels;
        LIST_ENTRY(teams_s) ptr;
    }teams_t;

    LIST_HEAD(te_l, teams_s);

    server_t init_server_struct(char *av[]);
    client_t *init_client(client_t *client);
    teams_t *init_teams(char *name, char *description, uuid_t c_uuid, char *uuid);
    channel_t *init_channel(char *name, char *desc, uuid_t team_uuid, char *uuid);
    thread_t *init_thread(char *title, char *msg, uuid_t chan_uuid, uuid_t user_uuid, 
        char *uuid);
    void clear_client_struct(client_t *client);

    void launch_server(char *av[], struct c_l *clients, struct te_l *team);

    int handle_client(server_t server, struct c_l *cli, struct te_l *tm);
    int connect_client(char *username, client_t *client);
    int get_client(server_t *server, struct c_l *clients);
    void print_info_team(teams_t *team, int fd, char *cmd);
    void print_info_threads(thread_t *thrd, int fd, char *cmd);
    void print_info_channel(channel_t *chan, int fd, char *cmd);
    void print_info_reply(thread_t *reply, int fd, char *cmd);
    void print_info_user(client_t *client, int fd, char *cmd);

    int check_args(int ac, char *av[]);
    int get_port(struct sockaddr_in addr);
    char *get_ip(struct sockaddr_in addr);
    int close_socket(int *socketfd);
    int disconnect_client(client_t *client);

    client_t *found_cli_by_uuid(const char *uuid, struct c_l *clients);
    teams_t *found_teams_by_uuid(const char *uuid, struct te_l *teams);
    channel_t *found_channel_by_uuid(const char *uuid, struct te_l *teams);
    thread_t *found_thread_by_uuid(const char *uuid, struct te_l *teams);

    int get_len(char *str, char c);
    int handle_command(char *cmd, client_t *client, server_t server);
    char *read_file(char *file);
    int get_username(client_t *client);
    int stock_username_in_file(client_t *client);
    void new_connection(client_t *client);
    void exec_cmd(char *buff, client_t *client, struct c_l *c, struct te_l *t);

    void info_command(client_t *client, struct te_l *t);
    void users_command(client_t *client, struct c_l *c);
    void user_command(client_t *client, struct c_l *c);
    void list_command(client_t *client, struct te_l *t);
    void create_command(client_t *client, struct te_l *t);
    void help_message(int fd);

#endif /* !teams_H_ */

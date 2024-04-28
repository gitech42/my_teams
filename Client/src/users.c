/*
** EPITECH PROJECT, 2022
** B-NWP-400-PAR-4-1-myteams-sacha.lliso
** File description:
** users
*/

#include "client.h"

void users_cmd()
{
    char *name = strtok(NULL, " \"\n");
    char *uuid = strtok(NULL, " \"\n");

    client_print_users(uuid, name, 1);
}

void user_cmd()
{
    char *name = strtok(NULL, " \"\n");
    char *uuid = strtok(NULL, " \"\n");

    client_print_user(uuid, name, 1);
}
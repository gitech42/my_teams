/*
** EPITECH PROJECT, 2022
** B-NWP-400-PAR-4-1-myteams-sacha.lliso
** File description:
** init
*/

#include "client.h"

cli_t *init_cli(cli_t *cli)
{
    cli->username = NULL;
    cli->used_enum = NOTHING;
    uuid_generate(cli->uuid);
    uuid_clear(cli->used_uuid);
    cli->current_used = NULL;
    return cli;
}
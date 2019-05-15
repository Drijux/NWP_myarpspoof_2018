/*
** EPITECH PROJECT, 2018
** MYARPSPOOF
** File description:
** handle_error.c
*/

#include <stdio.h>
#include <string.h>
#include <netdb.h>
#include <ctype.h>
#include "spoof.h"

static bool ismacaddr(char *str)
{
    int cpt = 0;

    if (str == NULL || strlen(str) != 17)
        return (false);
    for (int i = 0; str[i]; ++i) {
        if (str[i] != ':' && isxdigit(str[i]) != 0)
            cpt++;
        if ((str[i] != ':' && isxdigit(str[i]) == 0)
            || (str[i] == ':' && cpt != 2))
            return (false);
        if (str[i] == ':' && cpt == 2)
            cpt = 0;
    }
    return (true);
}

static bool check_add_arg(char **av)
{
    if (strcmp(av[0], "--printSpoof") != 0
        && strcmp(av[0], "--printBroadcast") != 0) {
        printf("Error: Argument not recognized: '%s'\n.", av[0]);
        return (false);
    }
    if (strcmp(av[0], "--printSpoof") == 0
        && !ismacaddr(av[1])) {
        printf("Error: Argument '%s' is not a MAC address.\n", av[1]);
        return (false);
    }
    return (true);
}

static bool first_arg(char **av)
{
    if (gethostbyname(av[0]) == NULL || gethostbyname(av[1]) == NULL) {
        printf("Error: %s: Bad IP\n", "gethostbyname");
        return (false);
    }
    return (true);
}

bool handle_error(int ac, char **av)
{
    if (!(ac >= 4 && ac <= 6)) {
        printf("Error: %s\n", NUM_INC);
        return (false);
    }
    if (!first_arg(av))
        return (false);
    if (ac >= 5 && !check_add_arg(av + 3))
        return (false);
    return (true);
}
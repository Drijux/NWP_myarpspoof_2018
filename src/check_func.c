/*
** EPITECH PROJECT, 2018
** MYARPSPOOF
** File description:
** check_func.c
*/

#include <stdio.h>
#include <string.h>
#include <sys/ioctl.h>
#include "spoof.h"


bool create_socket(int *sd, int domaine, int type, int protocol)
{
    if ((*sd = socket(domaine, type, protocol)) == -1) {
        perror("Failed to create socket");
        return (false);
    }
    return (true);
}

bool check_ioctl(int sd, int requete, struct ifreq *strc, char *name)
{
    memset(strc, 0, sizeof(struct ifreq));
    strncpy(strc->ifr_name, name, IFNAMSIZ);
    if (ioctl(sd, requete, strc) < 0) {
        if (requete == SIOCGIFINDEX)
            perror("Failed SIOCGIFINDEX");
        else
            perror("Failed SIOCGIFHWADDR");
        return (false);
    }
    return (true);
}
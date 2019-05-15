/*
** EPITECH PROJECT, 2018
** MYARPSPOOF
** File description:
** get_mac_addr.c
*/

#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include "spoof.h"

bool get_addr(char *str, char **mac_addr)
{
    char path[strlen("/sys/class/net/") + strlen(str) + 9];
    int fd = 0;

    sprintf(path, "%s%s%s", "/sys/class/net/", str, "/address");
    if ((fd = open(path, O_RDONLY)) == -1) {
        perror("Failed open");
        return (false);
    }
    if (read(fd, *mac_addr, 17) == -1) {
        perror("Failed read");
        return (false);
    }
    for (int i = 0; (*mac_addr)[i]; ++i) {
        if ((*mac_addr)[i] >= 'a' && (*mac_addr)[i] <= 'z')
            (*mac_addr)[i] = (*mac_addr)[i] - 32;
    }
    close(fd);
    return (true);
}

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
#include <stdlib.h>
#include "spoof.h"

bool get_addr_mac(arp_header_t *arp, char *name)
{
    char *mac_add = calloc(18, sizeof(char));
    char path[strlen("/sys/class/net/") + strlen(name) + 9];
    int fd = 0;

    sprintf(path, "%s%s%s", "/sys/class/net/", name, "/address");
    if (!mac_add || (fd = open(path, O_RDONLY)) == -1) {
        perror("Failed");
        return (false);
    }
    if (read(fd, mac_add, 17) == -1) {
        perror("Failed read");
        return (false);
    }
    sscanf(mac_add, "%hhx:%hhx:%hhx:%hhx:%hhx:%hhx:", &(arp->send_mac[0])
        , &(arp->send_mac[1]), &(arp->send_mac[2]), &(arp->send_mac[3])
        , &(arp->send_mac[4]), &(arp->send_mac[5]));
    free(mac_add);
    return (true);
}
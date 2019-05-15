/*
** EPITECH PROJECT, 2018
** MYARPSPOOF
** File description:
** arpspoof.c
*/

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include "spoof.h"

static bool arpspoof(int sd, int ifindex, struct ifreq *if_mac, char **av)
{
    (void)sd;
    char sendbuf[BUF_SIZE];
    struct ethhdr *send_req = (struct ethhdr *)sendbuf;
    arp_header_t arp;
    struct sockaddr_ll sock_addr;

    memset(sendbuf, 0, BUF_SIZE);
    fill_arp(&arp, ARP_REQUEST, NULL);
    fill_arp_eth(send_req, &arp, &sock_addr, if_mac);
    fill_sock_addr(&sock_addr, ifindex);
    fill_arp_send_target(&arp, av[0], av[1]);
    return (true);
}

int init_arpspoof(int ac, char **av)
{
    int sd = 0;
    int ifindex = 0;
    struct ifreq if_mac;

    if (ac >= 5)
        return (print_function(av));
    if (!create_socket(&sd))
        return (FAILURE);
    if (!check_ioctl(sd, SIOCGIFINDEX, &if_mac, av[2]))
        return (FAILURE);
    ifindex = if_mac.ifr_ifindex;
    if (!check_ioctl(sd, SIOCGIFHWADDR, &if_mac, av[2]))
        return (FAILURE);
    if (!arpspoof(sd, ifindex, &if_mac, av))
        return (FAILURE);
    close(sd);
    return (SUCCESS);
}
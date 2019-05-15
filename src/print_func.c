/*
** EPITECH PROJECT, 2018
** MYARPSPOOF
** File description:
** print_func.c
*/

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <netinet/ether.h>
#include <sys/ioctl.h>
#include <netinet/in.h>
#include "spoof.h"

static void printbroadcast(struct ifreq *if_mac, char **av)
{
    char sendbuf[BUF_SIZE];
    struct ethhdr *send_req = (struct ethhdr *)sendbuf;
    arp_header_t arp;
    struct sockaddr_ll sock_addr;

    memset(sendbuf, 0, BUF_SIZE);
    fill_arp_eth(send_req, &arp, &sock_addr, if_mac);
    fill_sock_addr(&sock_addr, 0);
    fill_arp(&arp, ARP_REQUEST);
    fill_arp_send_target(&arp, av[0], av[1]);
    print_arp_packet(&arp, send_req);
}

static void printspoof(struct ifreq *if_mac, char **av)
{
    (void)if_mac;
    (void)av;
    printf("--printSpoof\n");
}

int print_function(char **av)
{
    int sd = 0;
    struct ifreq if_mac;

    if (!create_socket(&sd, PF_INET, SOCK_STREAM, 0))
        return (FAILURE);
    if (!check_ioctl(sd, SIOCGIFHWADDR, &if_mac, av[2]))
        return (FAILURE);
    if (strcmp(av[0], "--printSpoof") == 0)
        printspoof(&if_mac, av);
    else
        printbroadcast(&if_mac, av);
    close(sd);
    return (SUCCESS);
}
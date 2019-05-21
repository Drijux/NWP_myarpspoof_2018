/*
** EPITECH PROJECT, 2018
** MYARPSPOOF
** File description:
** fill_function.c
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "spoof.h"

void fill_arp_send_target(arp_header_t *arp, char *sender, char *target)
{
    int ind_s = 0;
    int ind_d = 0;

    for (int i = 0; i < 4; ++i) {
        arp->sender_ip[i] = (unsigned char)atoi(sender + ind_s);
        ind_s = find_carac(sender, ind_s, '.') + 1;
        arp->target_ip[i] = (unsigned char)atoi(target + ind_d);
        ind_d = find_carac(target, ind_d, '.') + 1;
    }
}

void fill_arp_eth(struct ethhdr *send_req
    , arp_header_t *arp
    , struct sockaddr_ll *sock_addr
    , struct ifreq *if_mac)
{
    unsigned char save;

    for (int i = 0; i < 6; ++i) {
        send_req->h_dest[i] = (unsigned char)MY_DEST_MAC;
        arp->target_mac[i] = (unsigned char)0x00;
        save = arp->mac_addr[i] == -1
            ? (unsigned char)if_mac->ifr_hwaddr.sa_data[i]
            : (unsigned char)arp->mac_addr[i];
        send_req->h_source[i] = save;
        arp->sender_mac[i] = save;
        sock_addr->sll_addr[i] = save;
    }
    send_req->h_proto = htons(ETH_P_IP);
}

void fill_sock_addr(struct sockaddr_ll *sock_addr, int ifindex)
{
    sock_addr->sll_family = PF_PACKET;
    sock_addr->sll_protocol = htons(ETH_P_ARP);
    sock_addr->sll_ifindex = ifindex;
    sock_addr->sll_hatype = htons(ARPHRD_ETHER);
    sock_addr->sll_pkttype = (PACKET_BROADCAST);
    sock_addr->sll_halen = MAC_LENGTH;
    sock_addr->sll_addr[6] = 0x00;
    sock_addr->sll_addr[7] = 0x00;
}

void fill_arp(arp_header_t *arp, int opcode, char *mac_addr, int opt)
{
    int ind = 0;
    char save[3];

    arp->hardware_type = HW_TYPE;
    arp->protocol_type = htons(ETH_P_IP);
    arp->hardware_len = MAC_LENGTH;
    arp->protocol_len = IPV4_LENGTH;
    arp->opcode = opt == 1 ? opcode : htons(opcode);
    for (int i = 0; i < 6; ++i) {
        if (mac_addr == NULL)
            arp->mac_addr[i] = -1;
        else {
            sprintf(save, "%s", strncpy(save, mac_addr + ind, 2));
            arp->mac_addr[i] = hexa_to_decimal(save);
            ind += 3;
        }
    }
}
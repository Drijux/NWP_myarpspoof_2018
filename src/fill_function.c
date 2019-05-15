/*
** EPITECH PROJECT, 2018
** MYARPSPOOF
** File description:
** fill_function.c
*/

#include <stdio.h>
#include <stdlib.h>
#include "spoof.h"

void fill_arp_send_target(arp_header_t *arp, char *sender, char *target)
{
    int ind_s = 0;
    int ind_d = 0;

    for (int i = 0; i < 4; ++i) {
        arp->sender_ip[i] = atoi(sender + ind_s);
        ind_s = find_carac(sender, ind_s,'.') + 1;
        arp->target_ip[i] = atoi(target + ind_d);
        ind_d = find_carac(target, ind_d,'.') + 1;
    }
}

void fill_arp_eth(struct ethhdr *send_req
    , arp_header_t *arp
    , struct sockaddr_ll *sock_addr
    , struct ifreq *if_mac)
{
    for (int i = 0; i < 6; ++i) {
        send_req->h_dest[i] = MY_DEST_MAC;
        arp->target_mac[i] = MY_DEST_MAC;
        // arp->target_mac[i] = 0x00;
        send_req->h_source[i] = ((uint8_t *)&if_mac->ifr_hwaddr.sa_data)[i];
        arp->sender_mac[i] = ((uint8_t *)&if_mac->ifr_hwaddr.sa_data)[i];
        sock_addr->sll_addr[i] = ((uint8_t *)&if_mac->ifr_hwaddr.sa_data)[i];
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

void fill_arp(arp_header_t *arp, int opcode)
{
    arp->hardware_type = HW_TYPE;
    arp->protocol_type = htons(ETH_P_IP);
    arp->hardware_len = MAC_LENGTH;
    arp->protocol_len = IPV4_LENGTH;
    arp->opcode = opcode;
}
/*
** EPITECH PROJECT, 2018
** MYARPSPOOF
** File description:
** fill_function.c
*/

#include <stdio.h>
#include <stdlib.h>
#include "spoof.h"

char *fill_addr_mac(struct ifreq *send)
{
    char *mac_addr = calloc(18, sizeof(char));

    if (mac_addr == NULL)
        return (NULL);
    sprintf(mac_addr, "%02x:%02x:%02x:%02x:%02x:%02x"
        , (unsigned char)send->ifr_hwaddr.sa_data[0]
        , (unsigned char)send->ifr_hwaddr.sa_data[1]
        , (unsigned char)send->ifr_hwaddr.sa_data[2]
        , (unsigned char)send->ifr_hwaddr.sa_data[3]
        , (unsigned char)send->ifr_hwaddr.sa_data[4]
        , (unsigned char)send->ifr_hwaddr.sa_data[5]);
    for (int i = 0; mac_addr[i]; ++i) {
        if (mac_addr[i] >= 'a' && mac_addr[i] <= 'z')
            mac_addr[i] -= 32;
    }
    return (mac_addr);
}

void fill_struct_sockaddr(struct sockaddr_ll *sock_addr
    , int ifindex
    , arp_header_t *arp)
{
    for (int i = 0; i < MAC_LENGTH; ++i)
        sock_addr->sll_addr[i] = arp->send_mac[i];
    sock_addr->sll_family = PF_PACKET;
    sock_addr->sll_protocol = htons(ETH_P_ALL);
    sock_addr->sll_ifindex = ifindex;
    sock_addr->sll_hatype = htons(ARPHRD_ETHER);
    sock_addr->sll_pkttype = (PACKET_BROADCAST);
    sock_addr->sll_halen = MAC_LENGTH;
    sock_addr->sll_addr[6] = 0x00;
    sock_addr->sll_addr[7] = 0x00;
}

void fill_struct(arp_header_t *arp, unsigned short opcode)
{
    arp->type = PROTO_ARP;
    arp->hardware_type = HARD_TYPE;
    arp->protocol_type = PROTO_TYPE;
    arp->hardware_len = MAC_LENGTH;
    arp->protocol_len = IPV4_LENGTH;
    arp->opcode = opcode;
}

void fill_struct_ip(arp_header_t *arp, char *src, char *dest)
{
    sscanf(src, "%hhu.%hhu.%hhu.%hhu"
        , &(arp->send_ip[0]), &(arp->send_ip[1]), &(arp->send_ip[2])
        , &(arp->send_ip[3]));
    sscanf(dest, "%hhu.%hhu.%hhu.%hhu"
        , &(arp->targ_ip[0]), &(arp->targ_ip[1]), &(arp->targ_ip[2])
        , &(arp->targ_ip[3]));
}

void fill_struct_mac(arp_header_t *arp, const char *mac_addr)
{
    sscanf(mac_addr, "%hhx:%hhx:%hhx:%hhx:%hhx:%hhx:"
        , &(arp->targ_mac[0]), &(arp->targ_mac[1]), &(arp->targ_mac[2])
        , &(arp->targ_mac[3]), &(arp->targ_mac[4]), &(arp->targ_mac[5]));
    sscanf(mac_addr, "%hhx:%hhx:%hhx:%hhx:%hhx:%hhx:"
        , &(arp->mac_dist[0]), &(arp->mac_dist[1]), &(arp->mac_dist[2])
        , &(arp->mac_dist[3]), &(arp->mac_dist[4]), &(arp->mac_dist[5]));
    for (int i = 0; i < MAC_LENGTH; ++i)
        arp->mac_resp[i] = arp->send_mac[i];
}

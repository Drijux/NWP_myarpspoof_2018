/*
** EPITECH PROJECT, 2018
** MYARPSPOOF
** File description:
** print_arp.c
*/

#include <stdio.h>
#include "spoof.h"

static void print_arphdr(arp_header_t *arp)
{
    printf("%02x ", arp->protocol_type);
    printf("%02x ", arp->hardware_len);
    printf("00 %02x ", arp->hardware_type);
    printf("%02x 00 ", arp->protocol_type);
    printf("%02x ", arp->hardware_len);
    printf("%02x ", arp->protocol_len);
    printf("00 %02x ", arp->opcode);
}

void print_arp_packet(arp_header_t *arp, struct ethhdr *send_req)
{
    for (int i = 0; i < 6; ++i)
        printf("%02x ", send_req->h_dest[i]);
    for (int i = 0; i < 6; ++i)
        printf("%02x ", send_req->h_source[i]);
    print_arphdr(arp);
    for (int i = 0; i < 6; ++i)
        printf("%02x ", arp->sender_mac[i]);
    for (int i = 0; i < 4; ++i)
        printf("%02x ", arp->sender_ip[i]);
    for (int i = 0; i < 6; ++i)
        printf("%02x ", arp->target_mac[i]);
    for (int i = 0; i < 3; ++i)
        printf("%02x ", arp->target_ip[i]);
    printf("%02x\n", arp->target_ip[3]);
}
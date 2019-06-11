/*
** EPITECH PROJECT, 2019
** MyARPspoof
** File description:
** header
*/

#ifndef SPOOF_H_
#define SPOOF_H_

#include <arpa/inet.h>
#include <linux/if_packet.h>
#include <net/if.h>
#include <netinet/ether.h>
#include <stdbool.h>

#define SUCCESS     0
#define FAILURE     84
#define NUM_INC     "Number of arguments are incorrect."
#define BUF_SIZE    60

#define HARD_TYPE       0x0100
#define IPV4_LENGTH     0x04
#define MAC_LENGTH      0x06
#define ARP_REQUEST     0x0100
#define ARP_REPLY       0x0200
#define PROTO_TYPE      0x008
#define PROTO_ARP       0x0608
#define BROADCAST       "FF:FF:FF:FF:FF:FF"

typedef struct arp_header_s {
    unsigned char targ_mac[MAC_LENGTH];
    unsigned char send_mac[MAC_LENGTH];
    unsigned short type;
    unsigned short hardware_type;
    unsigned short protocol_type;
    unsigned char hardware_len;
    unsigned char protocol_len;
    unsigned short opcode;
    unsigned char mac_resp[MAC_LENGTH];
    unsigned char send_ip[IPV4_LENGTH];
    unsigned char mac_dist[MAC_LENGTH];
    unsigned char targ_ip[IPV4_LENGTH];
} arp_header_t;

bool handle_error(int , char **);
int init_arpspoof(int , char **);
bool create_socket(int *);
bool get_addr_mac(arp_header_t *, char *);
bool check_ioctl(int , int , struct ifreq *, char *);

void print_struct(void *, size_t );

void fill_struct_mac(arp_header_t *, const char *);
void fill_struct_ip(arp_header_t *, char *, char *);
void fill_struct(arp_header_t *, unsigned short );
void fill_struct_sockaddr(struct sockaddr_ll *, int , arp_header_t *);
char *fill_addr_mac(struct ifreq *);

void send_arp(int , arp_header_t *, struct sockaddr_ll *);
void receiv_arp(int , char **, arp_header_t *, int);
#endif

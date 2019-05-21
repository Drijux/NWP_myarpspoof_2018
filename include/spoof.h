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
#define BUF_SIZE    1024
#define MY_DEST_MAC 0xff

#define HW_TYPE     1
#define IPV4_LENGTH 4
#define MAC_LENGTH  6
#define ARP_REQUEST 0x01
#define ARP_REPLY   0x02
#define ETH2_HEADER_LEN 14
#define PROTO_ARP 0x0806
#define BROADCAST "FF:FF:FF:FF:FF:FF"

typedef struct arp_header_s {
    unsigned short hardware_type;
    unsigned short protocol_type;
    unsigned char hardware_len;
    unsigned char protocol_len;
    unsigned short opcode;
    unsigned char sender_mac[MAC_LENGTH];
    unsigned char sender_ip[IPV4_LENGTH];
    unsigned char target_mac[MAC_LENGTH];
    unsigned char target_ip[IPV4_LENGTH];
    int8_t mac_addr[MAC_LENGTH];
} arp_header_t;

typedef struct infohdr_s {
    unsigned char buf[BUF_SIZE];
    int ifindex;
    struct sockaddr_ll sock_addr;
    struct ethhdr *eth;
    struct ifreq if_mac;
    arp_header_t *arp;
} infohdr_t;

bool create_socket(int *sd);
bool check_ioctl(int sd, int requete, struct ifreq *strc, char *name);
int  print_function(char **av);
int hexa_to_decimal(char *hexVal);
bool handle_error(int ac, char **av);
bool get_addr(char *str, char **mac_addr);
int find_carac(char *str, int index, char carac);
void print_arp_packet(arp_header_t *arp, struct ethhdr *send_req);
int init_arpspoof(int ac, char **av);
void fill_arp_send_target(arp_header_t *arp, char *sender, char *target);
void fill_arp(arp_header_t *arp, int opcode, char *mac_addr, int opt);
void receiv_arp(int sd, infohdr_t *fsend, infohdr_t *rcv, char **av);
void send_arp(int sd, infohdr_t *send);
void loop_send(int sd, infohdr_t *send, char **av);
void print_victime(arp_header_t *arp_rep);
void fill_sock_addr(struct sockaddr_ll *sock_addr, int ifindex);
void fill_arp_eth(struct ethhdr *send_req
    , arp_header_t *arp
    , struct sockaddr_ll *sock_addr
    , struct ifreq *if_mac);
void prepare_last_send(infohdr_t *rcv
    , infohdr_t *fsend
    , infohdr_t *lsend
    , char **av);

#endif

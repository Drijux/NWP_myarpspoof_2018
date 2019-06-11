/*
** EPITECH PROJECT, 2018
** MYARPSPOOF
** File description:
** print_arp.c
*/

#include <stdio.h>
#include "spoof.h"

void print_struct(void *data, size_t size)
{
    for (uint8_t i = 0; i < (size - 1); ++i) {
        printf("%02x ", ((uint8_t *)data)[i]);
    }
    printf("%02x\n", ((uint8_t *)data)[size - 1]);
}
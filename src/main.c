/*
** EPITECH PROJECT, 2019
** MYARPSPOOF
** File description:
** main.c
*/

#include "spoof.h"

int main(int ac, char **av)
{
    if (!handle_error(ac, av + 1))
        return (FAILURE);
    return (init_arpspoof(ac, av + 1));
}
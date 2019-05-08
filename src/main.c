/*
** EPITECH PROJECT, 2019
** myFTP
** File description:
** main
*/

#include "spoof.h"

int main(int ac, char **av)
{
    if (!handle_error(ac, av + 1))
        return (FAILURE);
    return (SUCCESS);
}

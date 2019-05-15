/*
** EPITECH PROJECT, 2018
** MYARPSPOOF
** File description:
** find_carac.c
*/


#include <unistd.h>

int find_carac(char *str, int index, char carac)
{
    if (str == NULL)
        return (-1);
    for (int i = index; str[i]; ++i) {
        if (str[i] == carac)
            return (i);
    }
    return (0);
}
//
// Created by v_nicopolsky on 16/09/17.
//

#include "string_length.h"

int string_length(char const *string)
{
    int i = 0;

    while (*string != '\0')
    {
        string++;
        i++;
    }

    return i;
}
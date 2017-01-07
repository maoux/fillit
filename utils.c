#include "utils.h"

const char *byte_to_binary(int x)
{
    static char b[17];
    b[0] = '\0';

    int z;
    for (z = 32768; z > 0; z >>= 1)
    {
        ft_strcat(b, ((x & z) == z) ? "1" : "0");
    }

    return b;
}

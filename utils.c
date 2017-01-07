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

void print_pieces(const t_env * const pieces){
	for(int i = 0; i < pieces->size; i++){
        printf("Piece %d is %s\n", i, byte_to_binary(pieces->tab[i]));
    }
}

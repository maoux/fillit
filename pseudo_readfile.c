#include "fillit.h"

const t_env * const read_file(const char * const file_name)
{
	(void)file_name;
	t_env *pieces;
	
	pieces = ft_memalloc(sizeof(t_env));
	
	pieces->size = 4;
	pieces->tab = ft_memalloc(4 * sizeof(short int));
	pieces->tab[0] = 0b1100010001000000;
	pieces->tab[1] = 0b1111000000000000;
	pieces->tab[2] = 0b10001110000000000;
	pieces->tab[3] = 0b11000110000000000;
	return pieces;
}

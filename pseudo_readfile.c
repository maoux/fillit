#include "fillit.h"

const t_env * const read_file(const char * const file_name)
{
	(void)file_name;
	t_env *pieces;
	
	pieces = ft_memalloc(sizeof(t_env));
	
	pieces->size = 3;
	pieces->tab = ft_memalloc(3 * sizeof(short int));
	pieces->tab[0] = 0b0100010011000000;
	pieces->tab[1] = 0b1100110000000000;
	pieces->tab[2] = 0b1000100010001000;
//	pieces->tab[3] = 0b1000100010001000;
	return pieces;
}

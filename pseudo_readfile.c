#include "fillit.h"

t_env *read_file(const char * const file_name)
{
	(void)file_name;
	t_env *pieces;
	
	pieces = ft_memalloc(sizeof(t_env));
	
	pieces->size = 2;
	pieces->tab = ft_memalloc(2 * sizeof(short int));
	pieces->tab[0] = 0b1000100010001000;
	pieces->tab[1] = 0b1100110000000000;
	return pieces;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   piece_operation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agermain <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/10 16:14:08 by agermain          #+#    #+#             */
/*   Updated: 2017/01/10 17:16:23 by agermain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"
#include "utils.h"

t_ushort	*get_piece_size(unsigned short piece)
{
	t_ushort	*size;

	size = malloc(2 * sizeof(t_ushort));
	size[0] = 1;
	size[0] += piece & 0b0100010001000100 ? 1 : 0; // 0x4444
	size[0] += piece & 0b0010001000100010 ? 1 : 0; // 0x2222
	size[0] += piece & 0b0001000100010001 ? 1 : 0; // 0x1111
	size[1] = 1;
	size[1] += piece & 0b0000111100000000 ? 1 : 0; // 0x0F00
	size[1] += piece & 0b0000000011110000 ? 1 : 0; // 0x00F0
	size[1] += piece & 0b0000000000001111 ? 1 : 0; // 0x000F
	return (size);
}

t_ushort	get_pieces_size(t_env_cst pieces)
{
	t_ushort	w;
	t_ushort	h;
	unsigned char	i;
	t_ushort	*val;

	w = 0;
	h = 0;
	i = 0;
	while (i < pieces->size)
	{
		val = get_piece_size(pieces->tab[i++]);
		w += val[0];
		h += val[1];
		free(val);
	}
	printf("Max w%d h%d\n", w, h);
	return (h < w ? w : h);
}

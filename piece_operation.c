/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   piece_operation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agermain <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/10 16:14:08 by agermain          #+#    #+#             */
/*   Updated: 2017/01/29 22:00:58 by agermain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

t_ushort	*get_piece_size(unsigned short piece)
{
	t_ushort	*size;

	size = malloc(2 * sizeof(t_ushort));
	size[0] = 1;
	size[0] += piece & 0b0100010001000100 ? 1 : 0;
	size[0] += piece & 0b0010001000100010 ? 1 : 0;
	size[0] += piece & 0b0001000100010001 ? 1 : 0;
	size[1] = 1;
	size[1] += piece & 0b0000111100000000 ? 1 : 0;
	size[1] += piece & 0b0000000011110000 ? 1 : 0;
	size[1] += piece & 0b0000000000001111 ? 1 : 0;
	return (size);
}

t_ushort	get_pieces_size(t_pieces_cst pieces)
{
	t_ushort	w;
	t_ushort	h;
	t_uchar		i;
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
	return (h < w ? w : h);
}

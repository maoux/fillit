/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   place_piece.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agermain <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/29 17:15:35 by agermain          #+#    #+#             */
/*   Updated: 2017/01/31 17:02:26 by agermain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

static short int	cpl(
			t_ushort line,
			t_bmask *boardline,
			unsigned short x)
{
	t_ushort	board_cells;

	board_cells = *((t_ushort *)(&(((boardline))OFFSET(x))));
	return (board_cells & line ? 0 : 1);
}

static void			merge_lines(
			t_point_cst pt,
			t_board_cst board,
			char piece_sym,
			t_ushort *piece_l)
{
	t_ushort	line;
	t_ushort	*bit_mask;
	t_ushort	lval;
	t_ushort	bit_offset;

	 bit_offset = pt->x % 8;
	line = 0;
	while (line < 4 && pt->y + line < board->size)
	{
		lval = piece_l[line] << bit_offset;
		if (lval & 0x8000)
			board->board[pt->y + line][pt->x + 0] = piece_sym;
		if (lval & 0x4000)
			board->board[pt->y + line][pt->x + 1] = piece_sym;
		if (lval & 0x2000)
			board->board[pt->y + line][pt->x + 2] = piece_sym;
		if (lval & 0x1000)
			board->board[pt->y + line][pt->x + 3] = piece_sym;
		bit_mask = (t_ushort*)&((((t_bmask*)board->bit_mask[pt->y + line]))
								OFFSET(pt->x));
		(*bit_mask) |= piece_l[line];
		line++;
	}
}

#define PY pt->y
#define PX pt->x
t_board				*place_piece(
			t_ushort piece,
			t_board_cst b,
			t_point_cst pt,
			t_ushort piece_idx)
{
	t_board *stepboard;
	t_ushort l[4];
	t_ushort *piece_size;
	t_ushort bit_offset;

	piece_size = get_piece_size(piece);
	if (((PX + piece_size[0]) > b->size) ||
			((PY + piece_size[1]) > b->size))
		return (NULL);
	free(piece_size);
	bit_offset = PX % 8;
	l[0] = (((t_ushort)(piece & 0xF000)) << 0)  >> bit_offset;
	l[1] = (((t_ushort)(piece & 0x0F00)) << 4)  >> bit_offset;
	l[2] = (((t_ushort)(piece & 0x00F0)) << 8)  >> bit_offset;
	l[3] = (((t_ushort)(piece & 0x000F)) << 12) >> bit_offset;
	if(!((cpl(l[0], b->bit_mask[PY], PX)) &&
		 (!l[1] || (PY + 1 < b->size && cpl(l[1], b->bit_mask[PY + 1], PX))) &&
		 (!l[2] || (PY + 2 < b->size && cpl(l[2], b->bit_mask[PY + 2], PX))) &&
		 (!l[3] || (PY + 3 < b->size && cpl(l[3], b->bit_mask[PY + 3], PX)))))
		return (NULL);
	stepboard = duplicate_board(b);
	merge_lines(pt, stepboard, 'A' + piece_idx, l);
	stepboard->area = board_size(stepboard);
	return (stepboard);
}

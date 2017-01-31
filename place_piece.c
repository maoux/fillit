/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   place_piece.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agermain <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/29 17:15:35 by agermain          #+#    #+#             */
/*   Updated: 2017/02/01 00:41:15 by agermain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

static t_dbl_bmask	get_bit_mask(t_bmask *boardline, t_ushort x)
{
	t_dbl_bmask	bmask;
	t_bmask		*board_mask;

	board_mask = &((boardline)OFFSET(x));
	bmask.bmask[0] = board_mask[1];
	bmask.bmask[1] = board_mask[0];
	return bmask;
}

static short int	cpl(
			t_ushort line,
			t_bmask *boardline,
			unsigned short x)
{
	t_dbl_bmask	bmask;

	bmask = get_bit_mask(boardline, x);
	return (line & bmask.dbl_short ? 0 : 1);
}

static void			merge_lines(
			t_point_cst pt,
			t_board_cst board,
			char piece_sym,
			t_ushort *piece_l)
{
	t_ushort	line;
	t_ushort	lval;
	t_ushort	bit_offset;
	t_dbl_bmask	l_dbl;

	bit_offset = PX % 8;
	line = 0;
	while (line < 4 && PY + line < board->size)
	{
		lval = piece_l[line] << bit_offset;
		if (lval & 0x8000)
			board->board[PY + line][PX + 0] = piece_sym;
		if (lval & 0x4000)
			board->board[PY + line][PX + 1] = piece_sym;
		if (lval & 0x2000)
			board->board[PY + line][PX + 2] = piece_sym;
		if (lval & 0x1000)
			board->board[PY + line][PX + 3] = piece_sym;
		l_dbl.dbl_short = piece_l[line];
		board->bmask[PY + line][PX / 8 + 1] |= l_dbl.bmask[0];
		board->bmask[PY + line][PX / 8 + 0] |= l_dbl.bmask[1];
		line++;
	}
}

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
	if (	((PX + piece_size[0]) > b->size) ||
			((PY + piece_size[1]) > b->size))
		return (NULL);
	free(piece_size);
	bit_offset = PX % 8;
	l[0] = (((t_ushort)(piece & 0xF000)) << 0)  >> bit_offset;
	l[1] = (((t_ushort)(piece & 0x0F00)) << 4)  >> bit_offset;
	l[2] = (((t_ushort)(piece & 0x00F0)) << 8)  >> bit_offset;
	l[3] = (((t_ushort)(piece & 0x000F)) << 12) >> bit_offset;
	if(!(	(								cpl(l[0], b->bmask[PY + 0], PX))  &&
		((!l[1]) || (PY + 1 < b->size &&	cpl(l[1], b->bmask[PY + 1], PX))) &&
		((!l[2]) || (PY + 2 < b->size &&	cpl(l[2], b->bmask[PY + 2], PX))) &&
		((!l[3]) || (PY + 3 < b->size &&	cpl(l[3], b->bmask[PY + 3], PX)))))
		return (NULL);
	stepboard = duplicate_board(b);
	merge_lines(pt, stepboard, 'A' + piece_idx, l);
	stepboard->area = board_size(stepboard);
	return (stepboard);
}


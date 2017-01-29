/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   place_piece.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agermain <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/29 17:15:35 by agermain          #+#    #+#             */
/*   Updated: 2017/01/29 21:09:01 by agermain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

static short int can_place_line(t_ushort line, t_bmask *boardline, unsigned short x)
{
	t_ushort	board_cells;

	board_cells = *((t_ushort *)(&(((boardline))offset(x))));
	return (board_cells & line ? 0 : 1);
}

static void merge_lines(t_point_cst pt, t_board_cst board, char piece_sym, t_ushort *piece_l)
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
		bit_mask = &((((t_bmask*)board->bit_mask[pt->y + line]))offset(pt->x));
		(*bit_mask) |= piece_l[line];
		line++;
	}
}

t_board *place_piece(t_ushort piece, t_board_cst board, t_point_cst pt, t_ushort piece_idx)
{
	t_board *stepboard;
	t_ushort piece_l[4];
	t_ushort *piece_size;
	t_ushort line;
	t_ushort bit_offset;

	piece_size = get_piece_size(piece);
	if (((pt->x + piece_size[0]) > board->size) || ((pt->y + piece_size[1]) > board->size))
		return (NULL);
	free(piece_size);
	bit_offset = pt->x % 8;
	piece_l[0] = (((t_ushort)(piece & 0xF000)) << 0)  >> bit_offset;
	piece_l[1] = (((t_ushort)(piece & 0x0F00)) << 4)  >> bit_offset;
	piece_l[2] = (((t_ushort)(piece & 0x00F0)) << 8)  >> bit_offset;
	piece_l[3] = (((t_ushort)(piece & 0x000F)) << 12) >> bit_offset;
	if(!((can_place_line(piece_l[0], board->bit_mask[pt->y], pt->x)) &&
		 (!piece_l[1] || (pt->y + 1 < board->size && can_place_line(piece_l[1], board->bit_mask[pt->y + 1], pt->x))) &&
		 (!piece_l[2] || (pt->y + 2 < board->size && can_place_line(piece_l[2], board->bit_mask[pt->y + 2], pt->x))) &&
		 (!piece_l[3] || (pt->y + 3 < board->size && can_place_line(piece_l[3], board->bit_mask[pt->y + 3], pt->x)))))
        return (NULL);
    stepboard = duplicate_board(board);
	merge_lines(pt, stepboard, 'A' + piece_idx, piece_l);
	stepboard->area = board_size(stepboard);
	return (stepboard);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   place_piece.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agermain <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/29 17:15:35 by agermain          #+#    #+#             */
/*   Updated: 2017/01/29 18:17:52 by agermain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

static short int can_place_line(t_ushort line, t_bmask *boardline, unsigned short x)
{
	t_ushort	board_cells;

	board_cells = *((t_ushort *)(&(((boardline))offset(x))));
	return (board_cells & line ? 0 : 1);
}

static void merge_lines(t_point_cst pt, t_board_cst board, t_ushort piece_idx, t_ushort *piece_l)
{
	t_ushort	line;
	t_ushort	*bit_mask;

	line = 0;
	while (line < 4 && pt->y + line < board->size)
	{
		if(pt->x + 0 < board->size && (piece_l[line]) & 0x8000)
		{
			board->board[pt->y + line][pt->x + 0] = (char)'A' + piece_idx;
			if(pt->x + 1 < board->size && (piece_l[line]) & 0x4000)
			{
				board->board[pt->y + line][pt->x + 1] = (char)'A' + piece_idx;
				if(pt->x + 2 < board->size && (piece_l[line]) & 0x2000)
				{
					board->board[pt->y + line][pt->x + 2] = (char)'A' + piece_idx;
					if(pt->x + 3 < board->size && (piece_l[line]) & 0x1000)
						board->board[pt->y + line][pt->x + 3] = (char)'A' + piece_idx;
				}
			}
		}
		bit_mask = &((((t_bmask*)board->bit_mask[pt->y + line]))offset(pt->x));
		(*bit_mask) |= piece_l[line];
//(*(&((((t_bmask*)stepboard->bit_mask[y + line]))offset(x)))) |= piece_l[line];
		line++;
	}
}

t_board *place_piece(t_ushort piece, t_board_cst board, t_point_cst pt, t_ushort piece_idx)
{
	t_board		*stepboard;
	t_ushort	piece_l[4];
	t_ushort	*piece_size;
	t_ushort	line;
	t_ushort	bit_offset;

	piece_size = get_piece_size(piece);
	if (((pt->x + piece_size[0]) > board->size) || ((pt->y + piece_size[1]) > board->size))
		return (NULL);
	free(piece_size);
	bit_offset = pt->x % 8;
	piece_l[0] = (((t_ushort)(piece & 0xF000)) << 0);
	piece_l[1] = (((t_ushort)(piece & 0x0F00)) << 4);
	piece_l[2] = (((t_ushort)(piece & 0x00F0)) << 8);
	piece_l[3] = (((t_ushort)(piece & 0x000F)) << 12);
	if(!((can_place_line(piece_l[0] >> bit_offset, board->bit_mask[pt->y], pt->x)) &&
		 (!piece_l[1] || (pt->y + 1 < board->size && can_place_line(piece_l[1] >> bit_offset, board->bit_mask[pt->y + 1], pt->x))) &&
		 (!piece_l[2] || (pt->y + 2 < board->size && can_place_line(piece_l[2] >> bit_offset, board->bit_mask[pt->y + 2], pt->x))) &&
		 (!piece_l[3] || (pt->y + 3 < board->size && can_place_line(piece_l[3] >> bit_offset, board->bit_mask[pt->y + 3], pt->x)))))
        return (NULL);
    stepboard = duplicate_board(board);

	while (line < 4 && pt->y + line < board->size)
	{
		if(pt->x + 0 < board->size && (piece_l[line]) & 0x8000)
			stepboard->board[pt->y + line][pt->x + 0] = (char)'A' + piece_idx;
		if(pt->x + 1 < board->size && (piece_l[line]) & 0x4000)
			stepboard->board[pt->y + line][pt->x + 1] = (char)'A' + piece_idx;
		if(pt->x + 2 < board->size && (piece_l[line]) & 0x2000)
			stepboard->board[pt->y + line][pt->x + 2] = (char)'A' + piece_idx;
		if(pt->x + 3 < board->size && (piece_l[line]) & 0x1000)
			stepboard->board[pt->y + line][pt->x + 3] = (char)'A' + piece_idx;
		t_ushort *bit_mask = &((((t_bmask*)stepboard->bit_mask[pt->y + line]))offset(pt->x));
		(*bit_mask) |= piece_l[line];
		line++;
	}

//	merge_lines(pt, stepboard, piece_idx, piece_l);
	stepboard->area = board_size(stepboard);
	return (stepboard);
}

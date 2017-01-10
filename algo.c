/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agermain <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/07 18:20:29 by agermain          #+#    #+#             */
/*   Updated: 2017/01/10 18:55:27 by agermain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"
#include "utils.h"

static t_board *place_piece(unsigned short piece, t_board_cst board, unsigned short x, unsigned short y)
{
	const t_board	*stepboard;
	t_bmask			piece_l[4];
	unsigned short	*piece_size;

	printf("Trying at x=%d y=%d with piece=%s\n", x, y, byte_to_binary(piece));
	piece_size = get_piece_size(piece);
	if (((x + piece_size[0]) > board->size) || ((y + piece_size[1]) > board->size))
		return (NULL);
	stepboard = duplicate_board(board);
	piece_l[0] = piece & 0xF000;
	piece_l[1] = piece & 0x0F00;
	piece_l[2] = piece & 0x00F0;
	piece_l[3] = piece & 0x000F;



	free_board(stepboard);
	return (1);
}

static  void         f_b_p_rec(t_env_cst pieces, t_board_cst board, unsigned char piece_idx)
{
	unsigned short	x;
	unsigned short	y;
	t_board			*best_board;
	t_board			*tmp_board;

	printf("Doing piece %d: %s\n", piece_idx, byte_to_binary(pieces->tab[piece_idx]));
	y = 0;
	while (y < board->size)
	{
		printf("--- Doing l%d ---\n", y);
		x = 0;
		while (x < board->size)
		{
			tmp_board = place_piece(pieces->tab[piece_idx], board, x, y);
			printf("Return is %p\n", tmp_board);
			x++;
		}
		y++;
	}
}

int         find_best_placement(t_env_cst pieces)
{
	unsigned char piece_idx;

	piece_idx = 0;
//	while (piece_idx < pieces->size)
		
// Debug input pieces
	print_pieces(pieces);
	f_b_p_rec(pieces, create_board(get_pieces_size(pieces)), 0);

	return 0;
}

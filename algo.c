/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agermain <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/07 18:20:29 by agermain          #+#    #+#             */
/*   Updated: 2017/01/10 20:53:02 by agermain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"
#include "utils.h"

static short int	can_place_line(t_bmask line, t_bmask *boardline, unsigned short x)
{
	unsigned int	board_cells;
	t_bmask			board_cell;

	char *str1;
	char *str2;

	board_cells = boardline[x / 8];
	board_cells >>= (x % 8);
	board_cell = *((t_bmask*)(&board_cells));
	str1 = ft_strdup(byte_to_binary((unsigned int)line));
	str2 = ft_strdup(byte_to_binary((unsigned int)board_cell));
	printf("Piece_line=%s, table_line=%s\n", str1, str2);
	free(str1);
	free(str2);
	return (1);
}

static t_board *place_piece(unsigned short piece, t_board_cst board, unsigned short x, unsigned short y)
{
	const t_board	*stepboard;
	t_bmask			piece_l[4];
	unsigned short	*piece_size;
	unsigned short	line;

	printf("Trying at x=%d y=%d with piece=%s\n", x, y, byte_to_binary(piece));
	piece_size = get_piece_size(piece);
	if (((x + piece_size[0]) > board->size) || ((y + piece_size[1]) > board->size))
		return (NULL);
	stepboard = duplicate_board(board);
	// Extract each line of the piece
	piece_l[0] = (piece & 0xF000) >> 12;
	piece_l[1] = (piece & 0x0F00) >> 8;
	piece_l[2] = (piece & 0x00F0) >> 4;
	piece_l[3] = (piece & 0x000F);
	for(int i = 0; i < 4; i++){
			printf("Piece line @ %d is %s\n", i, byte_to_binary(piece_l[i]));
	}
	// For each line of the piece, if the piece line is empty OR if the table line is OK & placement could be done
	if((can_place_line(piece_l[0], board->bit_mask[y], x)) &&
	   (!piece_l[1] || (y + 1 < board->size && can_place_line(piece_l[1], board->bit_mask[y + 1], x))) &&
	   (!piece_l[2] || (y + 2 < board->size && can_place_line(piece_l[2], board->bit_mask[y + 2], x))) &&
	   (!piece_l[3] || (y + 3 < board->size && can_place_line(piece_l[3], board->bit_mask[y + 3], x))))
	{
		printf("Can place piece\n");
	}
	else
	{
		printf("CANNOT place piece\n");
	}

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

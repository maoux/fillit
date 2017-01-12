/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agermain <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/07 18:20:29 by agermain          #+#    #+#             */
/*   Updated: 2017/01/12 21:55:27 by agermain         ###   ########.fr       */
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
	board_cell = *((t_bmask*)(&board_cells));
	line <<= 4 - x;
	str1 = ft_strdup(byte_to_binary((unsigned int)line));
	str2 = ft_strdup(byte_to_binary((unsigned int)board_cell));
//	printf("Piece_line=%s, table_line=%s\n", str1, str2);
	free(str1);
	free(str2);
	return (board_cell & line ? 0 : 1);
}

static t_board *place_piece(unsigned short piece, t_board_cst board, unsigned short x, unsigned short y, unsigned short piece_idx)
{
	t_board			*stepboard;
	t_bmask			piece_l[4];
	unsigned short	*piece_size;
	unsigned short	line;

//	printf("Trying at x=%d y=%d with piece=%s\n", x, y, byte_to_binary(piece));
	piece_size = get_piece_size(piece);
	if (((x + piece_size[0]) > board->size) || ((y + piece_size[1]) > board->size))
		return (NULL);
	free(piece_size);
	// Extract each line of the piece
	piece_l[0] = (piece & 0xF000) >> 12;
	piece_l[1] = (piece & 0x0F00) >> 8;
	piece_l[2] = (piece & 0x00F0) >> 4;
	piece_l[3] = (piece & 0x000F);
/*	for(int i = 0; i < 4; i++){
		printf("Piece line @ %d is %s\n", i, byte_to_binary(piece_l[i]));
		}*/
	// For each line of the piece, if the piece line is empty OR if the table line is OK & placement could be done
	if((can_place_line(piece_l[0], board->bit_mask[y], x)) &&
	   (!piece_l[1] || (y + 1 < board->size && can_place_line(piece_l[1], board->bit_mask[y + 1], x))) &&
	   (!piece_l[2] || (y + 2 < board->size && can_place_line(piece_l[2], board->bit_mask[y + 2], x))) &&
	   (!piece_l[3] || (y + 3 < board->size && can_place_line(piece_l[3], board->bit_mask[y + 3], x))))
	{
		stepboard = duplicate_board(board);
//		printf("Can place piece\n");
		line = 0;
		while (line < 4 && y + line < stepboard->size)
		{
			stepboard->board[y + line][x + 0] = piece_l[line] & 0b1000 ? 'A' + piece_idx : stepboard->board[y + line][x + 0];
			stepboard->board[y + line][x + 1] = piece_l[line] & 0b0100 ? 'A' + piece_idx : stepboard->board[y + line][x + 1];
			stepboard->board[y + line][x + 2] = piece_l[line] & 0b0010 ? 'A' + piece_idx : stepboard->board[y + line][x + 2];
			stepboard->board[y + line][x + 3] = piece_l[line] & 0b0001 ? 'A' + piece_idx : stepboard->board[y + line][x + 3];
			unsigned short piece_L = (unsigned short)piece_l[line];
			piece_L <<= 4;
			piece_L >>= x;
			(stepboard->bit_mask[y+line])[x / BITS_PER_BMASK] += piece_L;
			line++;
		}
		return (stepboard);
	}
	else
	{
//		printf("CANNOT place piece\n");
		return (NULL);
	}

	return (NULL);
}

static inline unsigned short get_offset(t_bmask a)
{
	unsigned short i;
	i = 0;
	while (!((a << i) & 0b10000000))
		i++;
	return (i);
}

static inline unsigned short get_last_offset(t_bmask a)
{
	unsigned short i;
	i = 0;
	while (!((a >> i) & 0b00000001))
		i++;
	return (8 - i);
}

static inline unsigned short min(unsigned short a, unsigned short b)
{
	return (a < b ? a : b);
}

static inline unsigned short max(unsigned short a, unsigned short b)
{
	return (a > b ? a : b);
}

static unsigned short	**board_size(t_board_cst board)
{
	t_bmask	last_l_umask;
	unsigned short x;
	unsigned short y;
	unsigned short **ret;
	t_bmask		val;
	unsigned short shorts_count;

    shorts_count = (board->size / BITS_PER_BMASK) + ((board->size % BITS_PER_BMASK * 8) ? 1 : 0);
	ret = malloc(2 * sizeof(unsigned short *));
	ret[0] = ft_memalloc(2 * sizeof(unsigned short));
	ret[1] = ft_memalloc(2 * sizeof(unsigned short));
	ret[0][0] = board->size;
	ret[0][1] = board->size;
	last_l_umask = sum_n_bits(BITS_PER_BMASK - (board->size % (sizeof(t_bmask) * 8)));
	y = 0;
	while (y < board->size)
	{
		x = 0;
		while (x < shorts_count)
		{
			val = board->bit_mask[y][x];
			if (x == shorts_count - 1)
				val &= ~last_l_umask;
			if (val)
			{
				// Define Y
				ret[0][1] = min(ret[0][1], y);
				ret[1][1] = max(ret[1][1], y);
			
				// Define X
				ret[0][0] = min(ret[0][0], get_offset(val));
				ret[1][0] = max(ret[1][0], get_last_offset(val));
			}
			x++;
		}
		y++;
	}
//	printf("from %d:%d to %d:%d\n", ret[0][0], ret[0][1], ret[1][0], ret[1][1]);
	return (ret);
}

static t_board *get_best_board(t_board *candidate_board, t_board *best_board)
{
	unsigned short	**candidate_size;
	unsigned short	**best_size;
	unsigned short	i[2];
	unsigned short candidate_sq;
	unsigned short best_sq;

	if (candidate_board == NULL)
		return (best_board);
	if (best_board == NULL)
		return (candidate_board);
	candidate_size = board_size(candidate_board);
	candidate_sq = max(candidate_size[1][0] - candidate_size[0][0],
					   candidate_size[1][1] - candidate_size[0][1]);
	best_size = board_size(best_board);
	best_sq = max(best_size[1][0] - best_size[0][0],
				  best_size[1][1] - best_size[0][1]);
	if (candidate_sq > best_sq ||
		candidate_size[0][0] > best_size[0][0] ||
		candidate_size[0][1] > best_size[0][1])
	{
		free(candidate_size[0]);
		free(candidate_size[1]);
		free(candidate_size);
		free(best_size[0]);
		free(best_size[1]);
		free(best_size);
		return (best_board);
	}
	else 
	{
		if (candidate_sq == best_sq &&
			candidate_size[0][0] == best_size[0][0] &&
			candidate_size[0][1] == best_size[0][1])
		{
			free(candidate_size[0]);
			free(candidate_size[1]);
			free(candidate_size);
			free(best_size[0]);
			free(best_size[1]);
			free(best_size);
			return (best_board);
		}
		else
		{
			free(candidate_size[0]);
			free(candidate_size[1]);
			free(candidate_size);
			free(best_size[0]);
			free(best_size[1]);
			free(best_size);
			return (candidate_board);
		}
	}
}
static t_board	*choose_best_board(t_board *candidate_board, t_board *best_board)
{
	t_board *board;

	board = get_best_board(candidate_board, best_board);
	if (board == candidate_board)
	{
		if (best_board != NULL)
			free_board(best_board);
	}
	else
	{
		if (candidate_board != NULL)
			free_board(candidate_board);
	}
	return (board);
}

static short	abort_board(t_board_cst best_board_until, t_board_cst in_test)
{
	unsigned short a_size;
	unsigned short b_size;

	a_size = board_size(best_board_until);
	b_size = board_size(in_test);
}

static  t_board	*f_b_p_rec(t_env_cst pieces, t_board_cst board, unsigned char piece_idx)
{
	unsigned short	x;
	unsigned short	y;
	t_board			*best_board;
	t_board			*tmp_board;

	printf("Doing piece %d: %s\n", piece_idx, byte_to_binary(pieces->tab[piece_idx]));
	best_board = NULL;
	y = 0;
	while (y < board->size)
	{
		printf("--- Doing l%d ---\n", y);
		x = 0;
		while (x < board->size)
		{
			tmp_board = place_piece(pieces->tab[piece_idx], board, x, y, piece_idx);
			if (tmp_board != NULL) // If piece was posed OK ok the board
			{
			printf("Board taken piece idx %d\n", piece_idx);
				print_board(tmp_board);
				printf("\n\n");
//				if (get_best_board(tmp_board, best_board) != tmp_board)
//					free_board(tmp_board);
//				else
if (piece_idx < pieces->size)
					best_board = choose_best_board(f_b_p_rec(pieces, tmp_board, piece_idx + 1), best_board);
				else
					best_board = choose_best_board(tmp_board, best_board);
			}
			x++;
		}
		y++;
	}
	return (best_board);
}

int         find_best_placement(t_env_cst pieces)
{

	t_board	*best_board;
//	print_pieces(pieces);
	best_board = f_b_p_rec(pieces, create_board(get_pieces_size(pieces)), 0);
	printf("best board: %p\n", best_board);
	print_board(best_board);

	return 0;
}

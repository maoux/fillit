/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agermain <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/07 18:20:29 by agermain          #+#    #+#             */
/*   Updated: 2017/01/07 21:27:53 by agermain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"
#include "utils.h"

static t_board_cst create_board(unsigned short size)
{
	t_board *new_board;
	unsigned short i;

	new_board = malloc(sizeof(t_board));
	new_board->size = size;
	new_board->board = malloc(size * sizeof(char*));
	while (i < size)
		new_board->board[i++] = ft_memset(ft_memalloc(size * sizeof(char)), '.', size);
	return (new_board);	
}

static t_board_cst duplicate_board(t_board_cst board)
{
	t_board *new_board;
	unsigned short i;

	new_board = malloc(sizeof(t_board));
	new_board->size = board->size;
	new_board->board = malloc(board->size * sizeof(char*));
	while (i < board->size)
	{
		new_board->board[i] = ft_memcpy(malloc(board->size * sizeof(char)), board->board[i], board->size);
		i++;
	}
	return (new_board);	
}

static  void         f_b_p_rec(t_env_cst pieces, t_board_cst oldboard, unsigned char piece_idx)
{
	const t_board *stepboard;

	stepboard = duplicate_board(oldboard);
	print_board(stepboard);
}

int get_size(t_env_cst piece)
{
	int w;
	int h;
	unsigned char i;
	short int val;

	w = 0;
	h = 0;
	i = 0;
	while (i < piece->size)
	{
		val = piece->tab[i++];
		int p_w = 0,
			p_h = 0;
		p_w += 1;
		p_w += val & 0b0100010001000100 ? 1 : 0;
		p_w += val & 0b0010001000100010 ? 1 : 0;
		p_w += val & 0b00010001000100001 ? 1 : 0;
		p_h += 1;
		p_h += val & 0b0000111100000000 ? 1 : 0;
		p_h += val & 0b0000000011110000 ? 1 : 0;
		p_h += val & 0b0000000000001111 ? 1 : 0;
		printf("Piece %d w%d h%d\n", i, p_w, p_h);
		w += p_w;
		h += p_h;
	}
	printf("Max w%d h%d\n", w, h);
	return (h < w ? w : h);
}

int         find_best_placement(t_env_cst pieces)
{
	unsigned char piece_idx;

	piece_idx = 0;
//	while (piece_idx < pieces->size)
		
// Debug input pieces
	print_pieces(pieces);
	f_b_p_rec(pieces, create_board(get_size(pieces)), 0);

	return 0;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agermain <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/07 18:20:29 by agermain          #+#    #+#             */
/*   Updated: 2017/02/01 00:18:16 by agermain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

static t_board	*get_best_board(t_board *candidate, t_board *best)
{
	if (candidate == NULL)
		return (best);
	if (best == NULL)
		return (candidate);
	if (candidate->area >= best->area)
		return (best);
	else
		return (candidate);
}

static void		handle_tmp(
							t_pieces_cst pieces,
							t_board *tmp_board,
							unsigned char piece_idx,
							t_board **best)
{
	if (tmp_board != NULL)
	{
		if (get_best_board(tmp_board, *best) != tmp_board)
			free(tmp_board);
		else
		{
			if (piece_idx + 1 == pieces->size)
			{
				if (*best != NULL)
					free(*best);
				*best = tmp_board;
			}
			else
				f_b_p_rec(pieces, tmp_board, piece_idx + 1, best);
		}
	}
}

void			f_b_p_rec(
							t_pieces_cst pieces,
							t_board_cst board,
							unsigned char piece_idx,
							t_board **best)
{
	t_point		pt;
	t_board		*tmp_board;

	pt.y = 0;
	while (pt.y < board->size && ((*best) == NULL || (*best)->area >= pt.y))
	{
		pt.x = 0;
		while (pt.x < board->size && ((*best) == NULL || (*best)->area >= pt.x))
		{
			tmp_board = place_piece(pieces->tab[piece_idx],
									board, &pt, piece_idx);
			handle_tmp(pieces, tmp_board, piece_idx, best);
			pt.x++;
		}
		pt.y++;
	}
}

int				find_best_placement(t_pieces_cst pieces)
{
	t_board	*best_board;

	best_board = NULL;
	f_b_p_rec(pieces, create_board(get_pieces_size(pieces)), 0, &best_board);
	print_board(best_board);
	return (0);
}

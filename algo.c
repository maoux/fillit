/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agermain <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/07 18:20:29 by agermain          #+#    #+#             */
/*   Updated: 2017/01/29 21:53:26 by agermain         ###   ########.fr       */
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

static t_board	*choose_best_board(t_board *candidate, t_board *best)
{
	t_board *board;

	board = get_best_board(candidate, best);
	if (board == candidate)
	{
		if (best != NULL)
			free_board(best);
	}
	else
	{
		if (candidate != NULL)
			free_board(candidate);
	}
	return (board);
}

static t_ushort	handle_tmp_board(
									t_board *tmp,
									t_board **best,
									t_board **level_best,
									t_ushort is_last)
{
	if (tmp != NULL)
	{
		if (get_best_board(tmp, *best) != tmp)
		{
			free_board(tmp);
			return (-1);
		}
		else
		{
			if (is_last)
			{
				*level_best = choose_best_board(tmp, *level_best);
				*best = *level_best;
				return (0);
			}
			else
				return (1);
		}
	}
	return (-1);
}

static t_board	*f_b_p_rec(
							t_pieces_cst pieces,
							t_board_cst board,
							unsigned char piece_idx,
							t_board **best)
{
	t_point		pt;
	t_board		*best_board;
	t_board		*tmp_board;

	best_board = NULL;
	pt.y = 0;
	while (pt.y < board->size && ((*best) == NULL || (*best)->area >= pt.y))
	{
		pt.x = 0;
		while (pt.x < board->size && ((*best) == NULL || (*best)->area >= pt.x))
		{
			tmp_board = place_piece(pieces->tab[piece_idx],
									board, &pt, piece_idx);
			if (handle_tmp_board(tmp_board, best, &best_board,
								piece_idx + 1 == pieces->size) == 1)
				best_board = choose_best_board(f_b_p_rec(
						pieces, tmp_board, piece_idx + 1, best), best_board);
			pt.x++;
		}
		pt.y++;
	}
	return (best_board);
}

int				find_best_placement(t_pieces_cst pieces)
{
	t_board	*best_board;

	best_board = NULL;
	f_b_p_rec(pieces, create_board(get_pieces_size(pieces)), 0, &best_board);
	print_board(best_board);
	return (0);
}

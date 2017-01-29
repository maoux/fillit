/* ************************************************************************** *//*                                                                            *//*                                                        :::      ::::::::   *//*   algo.c                                             :+:      :+:    :+:   *//*                                                    +:+ +:+         +:+     *//*   By: agermain <marvin@42.fr>                    +#+  +:+       +#+        *//*                                                +#+#+#+#+#+   +#+           *//*   Created: 2017/01/07 18:20:29 by agermain          #+#    #+#             *//*   Updated: 2017/01/29 18:10:36 by agermain         ###   ########.fr       *//*                                                                            *//* ************************************************************************** */#include "fillit.h"static t_board *get_best_board(t_board *candidate_board, t_board *best_board){	t_ushort	*candidate_size;	t_ushort	*best_size;	if (candidate_board == NULL)		return (best_board);	if (best_board == NULL)		return (candidate_board);	candidate_size = candidate_board->area;	best_size = best_board->area;	if (candidate_size[2] >= best_size[2])		return (best_board);	else		return (candidate_board);}static t_board	*choose_best_board(t_board *candidate_board, t_board *best_board){	t_board *board;	board = get_best_board(candidate_board, best_board);	if (board == candidate_board)	{		if (best_board != NULL)			free_board(best_board);	}	else	{		if (candidate_board != NULL)			free_board(candidate_board);	}	return (board);}static  t_board	*f_b_p_rec(t_pieces_cst pieces, t_board_cst board, unsigned char piece_idx, t_board **best){	t_point		pt;	t_board		*best_board;	t_board		*tmp_board;	best_board = NULL;	pt.y = 0;	while (pt.y < board->size && ((*best) == NULL || (*best)->area[2] >= pt.y))	{		pt.x = 0;		while (pt.x < board->size && ((*best) == NULL || (*best)->area[2] >= pt.x))		{			tmp_board = place_piece(pieces->tab[piece_idx], board, &pt, piece_idx);			if (tmp_board != NULL)			{				if (get_best_board(tmp_board, *best) != tmp_board)					free_board(tmp_board);				else				{					if (piece_idx + 1 < pieces->size)						best_board = choose_best_board(f_b_p_rec(pieces, tmp_board, piece_idx + 1, best), best_board);					else					{						best_board = choose_best_board(tmp_board, best_board);						*best = best_board;					}				}			}			pt.x++;		}		pt.y++;	}	return (best_board);}int         find_best_placement(t_pieces_cst pieces){	t_board	*best_board;	best_board = NULL;	f_b_p_rec(pieces, create_board(get_pieces_size(pieces)), 0, &best_board);	print_board(best_board);	return (0);}
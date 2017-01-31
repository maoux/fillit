/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   board_operation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agermain <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/10 15:39:58 by agermain          #+#    #+#             */
/*   Updated: 2017/01/29 22:02:21 by agermain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

static t_bmask	sum_n_bits(t_ushort bits)
{
	t_bmask		ret;
	t_ushort	i;

	ret = 0;
	i = 0;
	while (i < bits)
	{
		ret += (1 << i);
		i++;
	}
	return (ret);
}

t_board			*create_board(t_ushort size)
{
	t_board		*new_board;
	t_ushort	i;
	t_ushort	shorts_count;

	i = 0;
	new_board = malloc(sizeof(t_board));
	new_board->size = size;
	new_board->board = malloc(size * sizeof(char*));
	shorts_count = (size / BITS_PER_BMASK)
		+ ((size % BITS_PER_BMASK) ? 1 : 0) + EXT_SIZE;
	new_board->bmask = malloc(size * sizeof(t_bmask*));
	while (i < size)
	{
		new_board->board[i] = ft_memset(ft_memalloc(size), '.', size);
		new_board->bmask[i] = ft_memset(ft_memalloc(shorts_count), 0,
											shorts_count);
		new_board->bmask[i][shorts_count - (1 + EXT_SIZE)] =
					(t_bmask)sum_n_bits(((BITS_PER_BMASK - (size % 8)) % 8));
		i++;
	}
	new_board->area = 0;
	return (new_board);
}

t_board			*duplicate_board(t_board_cst board)
{
	t_board		*new_board;
	t_ushort	i;
	t_ushort	shorts_count;

	i = 0;
	new_board = malloc(sizeof(t_board));
	new_board->size = board->size;
	new_board->board = malloc(board->size * sizeof(char*));
	shorts_count = (board->size / BITS_PER_BMASK) +
					((board->size % BITS_PER_BMASK) ? 1 : 0) + EXT_SIZE;
	new_board->bmask = malloc(board->size * sizeof(t_bmask*));
	while (i < board->size)
	{
		new_board->board[i] = ft_memcpy(malloc(board->size * sizeof(char)),
										board->board[i], board->size);
		new_board->bmask[i] = (t_bmask*)ft_memcpy(malloc(
			shorts_count * sizeof(t_bmask)), board->bmask[i], shorts_count);
		i++;
	}
	new_board->area = 0;
	return (new_board);
}

void			free_board(t_board *board)
{
	t_ushort	i;

	i = 0;
	while (i < board->size)
	{
		free(board->board[i]);
		free(board->bmask[i]);
		i++;
	}
	free(board->board);
	free(board->bmask);
	free(board);
}

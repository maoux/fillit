/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   board_operation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agermain <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/10 15:39:58 by agermain          #+#    #+#             */
/*   Updated: 2017/01/10 15:59:33 by agermain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"
#include "utils.h"

t_board_cst create_board(unsigned short size)
{
	t_board			*new_board;
	unsigned short	i;
	unsigned short	shorts_count;

	i = 0;
	new_board = malloc(sizeof(t_board));
	new_board->size = size;
	new_board->board = malloc(size * sizeof(char*));
	shorts_count = (size / 8) + (size % 8 ? 1 : 0);
	new_board->bit_mask = malloc(size * sizeof(t_bmask*));
	while (i < size)
	{
		new_board->board[i] = ft_memset(ft_memalloc(size * sizeof(char)), '.', size);
		new_board->bit_mask[i] = ft_memset(ft_memalloc(shorts_count / sizeof(t_bmask)), 0, shorts_count);
		i++;
	}
	return (new_board);	
}

t_board_cst duplicate_board(t_board_cst board)
{
	t_board			*new_board;
	unsigned short	i;
	unsigned short	shorts_count;

	i = 0;
	new_board = malloc(sizeof(t_board));
	new_board->size = board->size;
	new_board->board = malloc(board->size * sizeof(char*));
	shorts_count = (board->size / 8) + (board->size % 8 ? 1 : 0);
	new_board->bit_mask = malloc(board->size * sizeof(t_bmask*));
	while (i < board->size)
	{
		new_board->board[i] = ft_memcpy(malloc(board->size * sizeof(char)), board->board[i], board->size);
		new_board->bit_mask[i] = ft_memcpy(malloc(shorts_count * sizeof(t_bmask)), board->bit_mask[i], shorts_count);
		i++;
	}
	return (new_board);	
}

void	free_board(t_board *board)
{
	unsigned short	i;

	i = 0;
	while (i < board->size)
	{
		free(board->board[i]);
		free(board->bit_mask[i]);
		i++;
	}
	free(board->board);
	free(board->bit_mask);
	free(board);
}

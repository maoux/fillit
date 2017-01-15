/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   board_operation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agermain <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/10 15:39:58 by agermain          #+#    #+#             */
/*   Updated: 2017/01/15 16:52:56 by agermain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"
#include "utils.h"

t_bmask sum_n_bits(unsigned short bits)
{
	t_bmask ret;
	unsigned short i;

	ret = 0;
	i = 0;
	while (i <  bits)
	{
		ret += (1 << i);
		i++;
	}
	return (ret);
}

t_board		*create_board(unsigned short size)
{
	t_board			*new_board;
	unsigned short	i;
	unsigned short	shorts_count;

	i = 0;
	new_board = malloc(sizeof(t_board));
	new_board->size = size;
	new_board->board = malloc(size * sizeof(char*));
	shorts_count = (size / BITS_PER_BMASK) + ((size % BITS_PER_BMASK) ? 1 : 0);
//	printf("Using bmask of %d bytes\n", shorts_count);
	new_board->bit_mask = malloc(size * sizeof(t_bmask*));
	while (i < size)
	{
		new_board->board[i] = ft_memset(ft_memalloc(size * sizeof(char)), '.', size);
		new_board->bit_mask[i] = ft_memset(ft_memalloc(shorts_count), 0, shorts_count);
		new_board->bit_mask[i][shorts_count - 1] = (t_bmask)sum_n_bits(((BITS_PER_BMASK - (size % 8)) % 8));
//		printf("BMask board: %s\n", byte_to_binary(new_board->bit_mask[i][shorts_count - 1]));
		i++;
	}
	new_board->area = NULL;
	return (new_board);
}

t_board		*duplicate_board(t_board_cst board)
{
	t_board			*new_board;
	unsigned short	i;
	unsigned short	shorts_count;

	i = 0;
	new_board = malloc(sizeof(t_board));
	new_board->size = board->size;
	new_board->board = malloc(board->size * sizeof(char*));
	shorts_count = (board->size / BITS_PER_BMASK) + ((board->size % BITS_PER_BMASK) ? 1 : 0);
	new_board->bit_mask = malloc(board->size * sizeof(t_bmask*));
	while (i < board->size)
	{
		new_board->board[i] = ft_memcpy(malloc(board->size * sizeof(char)), board->board[i], board->size);


		unsigned short *bit_mask = &(((t_bmask*)board->bit_mask[i]))[shorts_count - 1];
		char *str = ft_strdup(byte_to_binary(*bit_mask));
//		printf("Dup board orig:   %s\n", str);
		new_board->bit_mask[i] = ft_memcpy(malloc(shorts_count), &(board->bit_mask[i][0]), shorts_count + 1);
		bit_mask = &(((t_bmask*)new_board->bit_mask[i]))[shorts_count - 1];
		str = ft_strdup(byte_to_binary(*bit_mask));
//		printf("Dup board new :   %s\n", str);
		i++;
	}
	new_board->area = NULL;
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
	if(board->area != NULL)
		free(board->area);
	free(board);
}

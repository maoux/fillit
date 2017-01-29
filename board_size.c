/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   board_size.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agermain <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/29 17:12:41 by agermain          #+#    #+#             */
/*   Updated: 2017/01/29 21:24:23 by agermain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

static inline t_ushort	max(t_ushort a, t_ushort b)
{
	return (a > b ? a : b);
}

t_ushort				board_size(t_board_cst board)
{
	t_ushort	x;
	t_ushort	y;
	t_point		ret;
	t_ushort	dim_max;

	ret.x = 0;
	ret.y = 0;
	y = 0;
	while (y < board->size)
	{
		x = 0;
		while (x < board->size)
		{
			if (board->board[y][x] != '.')
			{
				ret.y = max(ret.y, y + 1);
				ret.x = max(ret.x, x + 1);
			}
			x++;
		}
		y++;
	}
	dim_max = max(ret.x, ret.y);
	return (dim_max);
}

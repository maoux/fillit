/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   board_size.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agermain <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/29 17:12:41 by agermain          #+#    #+#             */
/*   Updated: 2017/01/29 17:18:43 by agermain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

static inline t_ushort max(t_ushort a, t_ushort b)
{
    return (a > b ? a : b);
}

t_ushort *board_size(t_board_cst board)
{
    t_ushort x;
    t_ushort y;
    t_ushort *ret;

    ret = malloc(3 * sizeof(t_ushort *));
    ret[0] = 0;
    ret[1] = 0;
    y = 0;
    while (y < board->size)
    {
        x = 0;
        while (x < board->size)
        {
            if (board->board[y][x] != '.')
            {
                ret[1] = max(ret[1], y + 1);
                ret[0] = max(ret[0], x + 1);
            }
            x++;
        }
        y++;
    }
    ret[2] = max(ret[0], ret[1]);
    return (ret);
}

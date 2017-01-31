/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agermain <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/07 18:56:18 by agermain          #+#    #+#             */
/*   Updated: 2017/02/01 00:12:10 by agermain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

void	print_board(t_board *board)
{
	char		*tmp;
	t_ushort	linec;

	linec = 0;
	if (board->area == 0)
		board->area = board_size(board);
	while (linec < board->area)
	{
		tmp = ft_strnew(board->area);
		ft_memcpy(tmp, board->board[linec], board->area);
		ft_putstr(tmp);
		ft_putchar('\n');
		free(tmp);
		linec++;
	}
}

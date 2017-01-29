/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agermain <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/07 18:56:18 by agermain          #+#    #+#             */
/*   Updated: 2017/01/29 21:59:22 by agermain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

void	print_board(t_board_cst board)
{
	char		*tmp;
	t_ushort	linec;

	linec = 0;
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

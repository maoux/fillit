/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agermain <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/07 18:56:18 by agermain          #+#    #+#             */
/*   Updated: 2017/01/07 19:02:46 by agermain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

void print_board(t_board_cst board)
{
	char *tmp;
	unsigned short linec;

	linec = 0;
	while (linec < board->size)
	{
		tmp = ft_strnew(board->size);
		ft_memcpy(tmp, board->board[linec], board->size);
		ft_putstr(tmp);
		ft_putchar('\n');
		free(tmp);
		linec++;
	}
}

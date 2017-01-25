/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heynard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/07 17:24:58 by heynard           #+#    #+#             */
/*   Updated: 2017/01/15 17:44:26 by agermain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLIT_H
# define FILLIT_H

# include "libft/includes/get_next_line.h"
# include "libft/includes/libft.h"
# include <fcntl.h>

# define BITS_PER_BMASK (sizeof(t_bmask) * 8)

typedef unsigned char	t_bmask;
typedef unsigned short	t_ushort;
typedef struct	s_pieces
{
	unsigned char	size;
	short int		*tab;
}				t_pieces;

typedef const t_pieces * const t_pieces_cst;
typedef struct s_board
{
	t_ushort	size; //No more than 26 chars, so no more than 26*4 width
	unsigned char	**board; //Keep track of pieces letters, so use chars (Each cell can be used by 27 different types)
	t_bmask	**bit_mask; // Same as board but in bits format
	t_ushort *area;
}	t_board;
typedef const t_board * const t_board_cst;

//fonction parsing appele par le main
int					find_best_placement(const t_pieces * const pieces);
void				print_board(t_board_cst board);

t_bmask sum_n_bits(t_ushort bits);
t_board	*create_board(t_ushort size);
t_board	*duplicate_board(t_board_cst board);
void    free_board(t_board *board);

t_ushort  *get_piece_size(unsigned short piece);
t_ushort  get_pieces_size(t_pieces_cst pieces);

//fonction parsing appele par le main
t_pieces		*read_file(const char *const file_name);
//fonction erreur appelant exit
void		error();

#include "utils.h"

#endif

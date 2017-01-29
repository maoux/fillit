/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heynard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/07 17:24:58 by heynard           #+#    #+#             */
/*   Updated: 2017/01/29 22:13:29 by agermain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLIT_H
# define FILLIT_H

# include "libft/includes/get_next_line.h"
# include "libft/includes/libft.h"
# include <fcntl.h>

# define BITS_PER_BMASK (sizeof(t_bmask) * 8)
# define EXT_SIZE 0
# define OFFSET(x) [((x) / 8)]

typedef unsigned char			t_bmask;
typedef unsigned short			t_ushort;
typedef unsigned char			t_uchar;
typedef struct					s_pieces
{
	unsigned char	size;
	t_ushort		*tab;
}								t_pieces;
typedef const t_pieces * const	t_pieces_cst;
typedef struct					s_board
{
	t_ushort		size;
	unsigned char	**board;
	t_bmask			**bit_mask;
	t_ushort		area;
}								t_board;
typedef const t_board * const	t_board_cst;
typedef struct					s_point
{
	t_ushort x;
	t_ushort y;
}								t_point;
typedef const t_point * const	t_point_cst;

int								find_best_placement(
				const t_pieces *const pieces);
void							print_board(t_board_cst board);
t_ushort						board_size(t_board_cst board);
t_board							*create_board(t_ushort size);
t_board							*duplicate_board(t_board_cst board);
void							free_board(t_board *board);
t_board							*place_piece(
				t_ushort piece,
				t_board_cst board,
				t_point_cst pt,
				t_ushort piece_idx);
t_ushort						*get_piece_size(unsigned short piece);
t_ushort						get_pieces_size(t_pieces_cst pieces);
int								check_env(t_pieces_cst env);
t_pieces						*read_file(
				const char *const file_name, int size);
void							error();

#endif

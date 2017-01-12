/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heynard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/07 17:24:58 by heynard           #+#    #+#             */
/*   Updated: 2017/01/10 20:55:05 by agermain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLIT_H
# define FILLIT_H

# include "libft/includes/get_next_line.h"
# include "libft/includes/libft.h"

typedef unsigned short	t_bmask;
typedef struct	s_env
{
	unsigned char	size;
	short int		*tab;
}				t_env;
typedef const t_env * const t_env_cst;
typedef struct s_board
{
	unsigned short	size; //No more than 26 chars, so no more than 26*4 width
	unsigned char	**board; //Keep track of pieces letters, so use chars (Each cell can be used by 27 different types)
	unsigned short	**bit_mask; // Same as board but in bits format
}	t_board;
typedef const t_board * const t_board_cst;

//fonction parsing appele par le main
const t_env	* const	read_file(const char * const file_name);
int					find_best_placement(const t_env * const pieces);
void				print_board(t_board_cst board);

t_board	*create_board(unsigned short size);
t_board	*duplicate_board(t_board_cst board);
void    free_board(t_board *board);

unsigned short  *get_piece_size(unsigned short piece);
unsigned short  get_pieces_size(t_env_cst pieces);
//fonction erreur appelant exit
void		error();

#endif

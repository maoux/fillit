/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heynard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/07 17:24:58 by heynard           #+#    #+#             */
/*   Updated: 2017/01/07 18:20:58 by agermain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLIT_H
# define FILLIT_H

# include "libft/includes/get_next_line.h"
# include "libft/includes/libft.h"

typedef struct	s_env
{
	unsigned char	size;
	short int		*tab;
}				t_env;

//fonction parsing appele par le main
const t_env		* const read_file(const char * const file_name);
int			find_best_placement(const t_env * const pieces);

//fonction erreur appelant exit
void		error();

#endif

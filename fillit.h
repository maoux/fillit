/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heynard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/07 17:24:58 by heynard           #+#    #+#             */
/*   Updated: 2017/01/12 18:07:32 by heynard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLIT_H
# define FILLIT_H

# include "libft/libft.h"

# include <fcntl.h>
# include <stdio.h>

typedef struct	s_env
{
	unsigned char		size;
	unsigned short int	*tab;
}				t_env;

//fonction parsing appele par le main
t_env		*read_file(char const *file_name);
int			check_env(t_env *env);

//fonction erreur appelant exit
void		error();

//fonctions test
const char	*byte_to_binary(int x);
void		print_pieces(const t_env *pieces);

#endif

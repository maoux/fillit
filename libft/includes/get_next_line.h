/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agermain <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/02 16:11:43 by agermain          #+#    #+#             */
/*   Updated: 2017/01/07 17:36:39 by heynard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

/*
** # define MAX_BUFF_SIZE 4193271
*/
# define BUFF_SIZE 512
# define MIN_BUFF_SIZE 1

/*
** # if MAX_BUFF_SIZE < BUFF_SIZE
** #  define B_BUFF_SIZE MAX_BUFF_SIZE
** # elif MIN_BUFF_SIZE > BUFF_SIZE
** #  define B_BUFF_SIZE MIN_BUFF_SIZE
** # else
** #  define B_BUFF_SIZE BUFF_SIZE
*/

# if MIN_BUFF_SIZE > BUFF_SIZE
#  define B_BUFF_SIZE MIN_BUFF_SIZE
# else
#  define B_BUFF_SIZE BUFF_SIZE
# endif

typedef struct	s_gnl {
	int		size;
	char	**buffers;
	int		*fds;
}				t_gnl;

int				get_next_line(const int fd, char **line);

#endif

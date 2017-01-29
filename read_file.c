/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heynard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/07 17:56:05 by heynard           #+#    #+#             */
/*   Updated: 2017/01/29 20:42:23 by agermain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

static int		ft_size_file(const char *file_name)
{
	char		buffer;
	int			fd;
	int			size;

	size = 0;
	if ((fd = open(file_name, O_RDONLY)) < 0)
		error();
	while (read(fd, &buffer, 1))
	{
		size++;
		if (size > 546)
			error();
	}
	close(fd);
	return (size);
}

static t_ushort	check_buffer(char *buffer)
{
	t_ushort		piece;
	int			position;
	int			i;

	piece = 0x0000;
	position = 0;
	i = 0;
	if (buffer[4] != '\n'
		|| buffer[9] != '\n'
		|| buffer[14] != '\n'
		|| buffer[19] != '\n')
		error();
	while (i < 19)
	{
		if (buffer[i] == '#')
			piece = piece | (0x8000 >> position);
		if ((i != 4 && i != 9 && i != 14) || i == 0)
		{
			if (buffer[i] != '.' && buffer[i] != '#')
				error();
			position++;
		}
		i++;
	}
	return (piece);
}

static t_pieces	*init_pieces(t_pieces *env, const char *pieces, int i, int j)
{
	t_ushort		*tab;
	char		*buffer;
	int			k;

	if ((tab = (t_ushort *)malloc(sizeof(t_ushort) * 26)) == NULL)
		error();
	k = 0;
	buffer = ft_strnew(21);
	while (pieces[i] != '\0')
	{
		buffer[k++] = pieces[i];
		if (k == 21 || pieces[i + 1] == '\0')
		{
			tab[j++] = check_buffer(buffer);
			k = 0;
		}
		i++;
	}
	if (pieces[i - 1] != '\n'
		|| (pieces[i - 2] != '.' && pieces[i - 2] != '#'))
		error();
	env->tab = tab;
	env->size = (unsigned char)j;
	return (env);
}

t_pieces			*read_file(const char *file_name)
{
	t_pieces		*env;
	char		*pieces;
	char		buf;
	int			size;
	int			fd;
	int			i;

	i = 0;
	size = ft_size_file(file_name);
	if ((fd = open(file_name, O_RDONLY)) < 0)
		error();
	pieces = ft_strnew(size);
	while (read(fd, &buf, 1))
	{
		pieces[i] = buf;
		i++;
	}
	pieces[i] = '\0';
	close(fd);
	if ((env = malloc(sizeof(t_pieces))) == NULL)
		error();
	env = init_pieces(env, pieces, 0, 0);
	return (env);
}
